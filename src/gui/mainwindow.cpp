#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "torrentcreatordialog.h"

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
