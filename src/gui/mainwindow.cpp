#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "torrentcreatordialog.h"
#include "addtorrentfiledialog.h"
#include "generatekeypairdialog.h"

#include <libtorrent/alert_types.hpp>
#include <libtorrent/bdecode.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/disk_io_thread.hpp>
#include <libtorrent/error_code.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>
#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent/extensions/smart_ban.hpp>
#include <libtorrent/identify_client.hpp>
#include <libtorrent/ip_filter.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/session_stats.hpp>
#include <libtorrent/session_status.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/version.hpp>
#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/alert_types.hpp>

#include <fstream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , ui_{new Ui::MainWindow}
{
    ui_->setupUi(this);
    setWindowTitle("cryptoBT");
    setWindowIcon(QIcon(":/icons/logo.png"));

    // Set icons
    ui_->toolBar->setIconSize(QSize(30, 30));
    ui_->actionAddTorrentLink->setIcon(QIcon(":/icons/insert-link.svg"));
    ui_->actionAddTorrentFile->setIcon(QIcon(":/icons/list-add.svg"));
    ui_->actionCreateNewTorrent->setIcon(QIcon(":/icons/document-edit.svg"));
    ui_->actionExit->setIcon(QIcon(":/icons/application-exit.svg"));
    ui_->actionPause->setIcon(QIcon(":/icons/media-playback-pause.svg"));
    ui_->actionResume->setIcon(QIcon(":/icons/media-playback-start.svg"));
    ui_->actionDelete->setIcon(QIcon(":/icons/list-remove.svg"));
    ui_->actionNewKeyPair->setIcon(QIcon(":/icons/gen-new-key-pair.svg"));
    ui_->actionImportPublicKey->setIcon(QIcon(":/icons/add-user.svg"));
    ui_->actionListPublicKeys->setIcon(QIcon(":/icons/list-public-keys.svg"));
    ui_->actionPreferences->setIcon(QIcon(":/icons/gear.svg"));
    ui_->actionFAQ->setIcon(QIcon(":/icons/help-contents.svg"));
    ui_->actionAbout->setIcon(QIcon(":/icons/help-about.svg"));

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui_->toolBar->addWidget(spacer);
    ui_->toolBar->addAction(ui_->actionPreferences);

    createKeyboardShortcuts();

    connect(ui_->actionNewKeyPair, &QAction::triggered, this, &MainWindow::onGenerateNewKeyPairTriggered);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::createKeyboardShortcuts()
{
    ui_->actionAddTorrentFile->setShortcut(QKeySequence::Open);
    ui_->actionAddTorrentLink->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    ui_->actionCreateNewTorrent->setShortcut(QKeySequence::New);
    ui_->actionExit->setShortcut(Qt::CTRL + Qt::Key_Q);

    ui_->actionResume->setShortcut(Qt::CTRL + Qt::Key_S);
    ui_->actionPause->setShortcut(Qt::CTRL + Qt::Key_P);
    ui_->actionDelete->setShortcut(QKeySequence::Delete);
    ui_->actionPreferences->setShortcut(Qt::ALT + Qt::Key_O);

    ui_->actionNewKeyPair->setShortcut(Qt::CTRL + Qt::Key_G);
    ui_->actionImportPublicKey->setShortcut(Qt::CTRL + Qt::Key_I);
}

void MainWindow::downloadFromURLList(const QStringList &urlList)
{
//    const bool useTorrentAdditionDialog = AddNewTorrentDialog::isEnabled();
//    for (const QString &url : urlList) {
//        if (useTorrentAdditionDialog)
//            AddNewTorrentDialog::show(url, this);
//        else
//            BitTorrent::Session::instance()->addTorrent(url);
//    }
}

void MainWindow::about()
{
    QLabel *icon = new QLabel;
    icon->setPixmap(QPixmap(":/icons/logo.png"));

    QLabel *text = new QLabel;
    text->setWordWrap(true);
    text->setText("<h2>crytoBT 0.0.1</h2>"
                  "<p>A secure and easy BitTorrent Client programmed in C++,"
                  " based on Qt toolkit, crypto++ and libtorrent-rasterbar.</p>");

    QPushButton *quitButton = new QPushButton("OK");

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setMargin(10);
    topLayout->setSpacing(10);
    topLayout->addWidget(icon);
    topLayout->addWidget(text);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(quitButton);
    bottomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    QDialog about(this);
    about.setModal(true);
    about.setWindowTitle(tr("About cryptBT"));
    about.setLayout(mainLayout);
    about.layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(quitButton, &QPushButton::clicked, &about, &QDialog::close);

    about.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    about();
}

void MainWindow::on_actionCreateNewTorrent_triggered()
{
    torrent_creator_dlg_ = new TorrentCreatorDialog(this);
    torrent_creator_dlg_->show();
}

void MainWindow::on_actionAddTorrentLink_triggered()
{
//    if (!download_from_URL_dlg_) {
//        download_from_URL_dlg_ = new DownloadFromURLDialog(this);
//        connect(download_from_URL_dlg_.data(), &DownloadFromURLDialog::urlsReadyToBeDownloaded,
//                this, &MainWindow::downloadFromURLList);
//    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::onGenerateNewKeyPairTriggered()
{
    key_pair_dlg_ = new GenerateKeyPairDialog(this);
    key_pair_dlg_->show();
}

void MainWindow::on_actionAddTorrentFile_triggered()
{
    const QString torrent_file = QFileDialog::getOpenFileName(this, tr("Choose torrent file"), QDir::homePath(), tr("Torrent Files (*.torrent)"));
    if (torrent_file.isEmpty())
        return;

    add_torrent_file_dlg_ = new AddTorrentFileDialog(this, torrent_file);
    add_torrent_file_dlg_->show();

/** Downloading torrent-files with creating torrent session
    const QString torrent_name = QFileDialog::getOpenFileName(this, tr("Open Torrent files"), QDir::homePath(), tr("Torrent Files (*.torrent)"));
    const QString download_location = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    const int alertMask = lt::alert::error_notification
                    | lt::alert::port_mapping_notification
                    | lt::alert::storage_notification
                    | lt::alert::tracker_notification
                    | lt::alert::status_notification
                    | lt::alert::ip_block_notification
                    | lt::alert::file_progress_notification
                    | lt::alert::stats_notification;
try {
    lt::settings_pack pack;
    pack.set_int(lt::settings_pack::alert_mask, alertMask);
    pack.set_bool(lt::settings_pack::listen_system_port_fallback, false);
    pack.set_bool(lt::settings_pack::use_dht_as_fallback, false);
    // Disable support for SSL torrents for now
    pack.set_int(lt::settings_pack::ssl_listen, 0);
    // To prevent ISPs from blocking seeding
    pack.set_bool(lt::settings_pack::lazy_bitfields, true);
    // Speed up exit
    pack.set_int(lt::settings_pack::stop_tracker_timeout, 1);
    pack.set_int(lt::settings_pack::auto_scrape_interval, 1200); // 20 minutes
    pack.set_int(lt::settings_pack::auto_scrape_min_interval, 900); // 15 minutes
    pack.set_int(lt::settings_pack::connection_speed, 20); // default is 10
    pack.set_bool(lt::settings_pack::no_connect_privileged_ports, false);
    pack.set_bool(lt::settings_pack::use_disk_cache_pool, false);

    pack.set_bool(lt::settings_pack::enable_upnp, true);
    pack.set_bool(lt::settings_pack::enable_natpmp, true);
    pack.set_bool(lt::settings_pack::upnp_ignore_nonrouters, true);
    pack.set_bool(lt::settings_pack::allow_multiple_connections_per_ip, true);
    pack.set_bool(lt::settings_pack::enable_dht, true);
    pack.set_str(lt::settings_pack::dht_bootstrap_nodes, "dht.libtorrent.org:25401,router.bittorrent.com:6881,router.utorrent.com:6881,dht.transmissionbt.com:6881,dht.aelitis.com:6881");
    pack.set_bool(lt::settings_pack::enable_lsd, true);

    lt::session *native_session_ = new lt::session {pack, int{0}};

    native_session_->add_extension(&lt::create_ut_metadata_plugin);
    native_session_->add_extension(&lt::create_ut_pex_plugin);
    qDebug("* BitTorrent Session constructed");

    std::ifstream in(torrent_name.toStdString(), std::ios_base::binary);
    in.unsetf(std::ios_base::skipws);
    lt::entry e = lt::bdecode(std::istream_iterator<char>(in), std::istream_iterator<char>());
    native_session_->add_torrent(lt::torrent_info(e), download_location.toStdString());

    for (;;) {
        std::vector<lt::alert*> alerts;
        native_session_->pop_alerts(&alerts);

        for (lt::alert const* a : alerts) {
          std::cout << a->message() << std::endl;
          // if we receive the finished alert or an error, we're done
          if (lt::alert_cast<lt::torrent_finished_alert>(a)) {
            goto done;
          }
          if (lt::alert_cast<lt::torrent_error_alert>(a)) {
            goto done;
          }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
done:
      std::cout << "done, shutting down" << std::endl;
      delete native_session_;
}
catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
}
//    lt::add_torrent_params atp;
//    atp.save_path = download_location.toStdString(); // save in current dir
//    lt::torrent_handle h = ses.add_torrent(std::move(atp));
*/
}
