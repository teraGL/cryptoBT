#include "torrentcreatordialog.h"
#include "ui_torrentcreatordialog.h"

#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>

//#include "core/bittorrent/session.h"
//#include "core/bittorrent/torrentcreatorthread.h"
//#include "core/bittorrent/torrentinfo.h"

TorrentCreatorDialog::TorrentCreatorDialog(QWidget* parent, const QString& defautPath)
    : QDialog{parent}
    , ui_{new Ui::TorrentCreatorDialog}
{
    ui_->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(false);

    ui_->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Create Torrent"));

    connect(ui_->btnAddFile, &QPushButton::clicked, this, &TorrentCreatorDialog::onAddFileButtonClicked);
    connect(ui_->btnAddFolder, &QPushButton::clicked, this, &TorrentCreatorDialog::onAddFolderButtonClicked);
    connect(ui_->buttonBox, &QDialogButtonBox::accepted, this, &TorrentCreatorDialog::onCreateButtonClicked);

//    connect(creatorThread_, &BitTorrent::TorrentCreatorThread::creationSuccess, this, &TorrentCreatorDialog::handleCreationSuccess);
//    connect(creatorThread_, &BitTorrent::TorrentCreatorThread::creationFailure, this, &TorrentCreatorDialog::handleCreationFailure);
//    connect(creatorThread_, &BitTorrent::TorrentCreatorThread::updateProgress, this, &TorrentCreatorDialog::updateProgressBar);

    updateInputPath(defautPath);

    show();
}

TorrentCreatorDialog::~TorrentCreatorDialog()
{
    qDebug() << "Removed TorrentCreatorDialog...";
//    saveSettings();
    delete ui_;
}


QString createDefaultSeedingDir(const QString& filepath)
{
    QString documents_dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    qDebug() << "Standard Documents dir =" << documents_dir << "\n";

    if (!documents_dir.contains("Documents")) {
        documents_dir += "/Documents";
        QDir().mkdir(documents_dir);
        qDebug() << "Created '~/Documents' successfully!\n";
    }

    const QString seeding_dir = documents_dir + "/cryptoBT/Seeding/";
    if (!QDir(seeding_dir).exists()) {
        QDir().mkpath(seeding_dir);
        qDebug() << "Created '~/Documents/cryptBT/Seeding' successfully!\n";
    }

    const QString outFile = seeding_dir + QFileInfo(filepath).fileName() + ".enf";
    qDebug() << "Output file: " << outFile;

    return outFile;
}

void TorrentCreatorDialog::updateInputPath(const QString &path)
{
    if (path.isEmpty()) return;
    ui_->textInputPath->setText(QDir::toNativeSeparators(path));
}

void TorrentCreatorDialog::onAddFileButtonClicked()
{
    const QString old_path = ui_->textInputPath->text();
    const QString filepath = QFileDialog::getOpenFileName(this, tr("Choose a file"), old_path);
    updateInputPath(filepath);
    qDebug() << "file:" << filepath;
}

void TorrentCreatorDialog::onAddFolderButtonClicked()
{
    const QString old_path = ui_->textInputPath->text();
    const QString dirpath = QFileDialog::getExistingDirectory(this, tr("Choose a folder"), old_path);
    updateInputPath(dirpath);
    qDebug() << "folder:" << dirpath;
}

void TorrentCreatorDialog::onCreateButtonClicked()
{
    QString input = QDir::fromNativeSeparators(ui_->textInputPath->text()).trimmed();

    // test if readable
    const QFileInfo fi(input);
    if (!fi.isReadable()) {
        QMessageBox::critical(this, tr("Torrent creation failed"), tr("Reason: Path to file/folder is not readable."));
        return;
    }
    input = fi.canonicalFilePath();

    // get save path
    const QString savePath = QString(QDir::homePath()) + QLatin1Char('/') + fi.fileName() + QLatin1String(".torrent");
    QString destination = QFileDialog::getSaveFileName(this, tr("Select where to save the new torrent"), savePath, tr("Torrent Files (*.torrent)"));
    if (destination.isEmpty())
        return;
    if (!destination.endsWith(".torrent", Qt::CaseInsensitive))
        destination += ".torrent";

    // Disable dialog & set busy cursor
    setInteractionEnabled(false);
    setCursor(QCursor(Qt::WaitCursor));

    const QStringList trackers = ui_->textTrackersURLs->toPlainText().trimmed()
        .replace(QRegularExpression("\n\n[\n]+"), "\n\n").split('\n');
    const QString comment = ui_->lineComment->text();

//    const QString default_seeding_dir = createDefaultSeedingDir(ui_->textInputPath->text());

    // 1) Encrypt file/folder
    // 2) Save Secret Key & IV
    // 3) default_seeding_dir = createDefaultSeedingDir(ui_->textInputPath->text());
    //    updateInputPath(default_seeding_dir);
    // 4)
}

void TorrentCreatorDialog::handleCreationFailure(const QString &msg)
{
    // Remove busy cursor
    setCursor(QCursor(Qt::ArrowCursor));
    QMessageBox::information(this, tr("Torrent creation failed"), tr("Reason: %1").arg(msg));
    setInteractionEnabled(true);
}

void TorrentCreatorDialog::handleCreationSuccess(const QString &path, const QString &branchPath)
{
    // Remove busy cursor
    setCursor(QCursor(Qt::ArrowCursor));
//    if (ui_->checkStartSeeding->isChecked()) {
//        // Create save path temp data
//        BitTorrent::TorrentInfo t = BitTorrent::TorrentInfo::loadFromFile(Utils::Fs::toNativePath(path));
//        if (!t.isValid()) {
//            QMessageBox::critical(this, tr("Torrent creation failed"), tr("Reason: Created torrent is invalid. It won't be added to download list."));
//            return;
//        }

//        BitTorrent::AddTorrentParams params;
//        params.savePath = branchPath;
//        params.skipChecking = true;
//        params.ignoreShareLimits = ui_->checkIgnoreShareLimits->isChecked();

//        BitTorrent::Session::instance()->addTorrent(t, params);
//    }
//    QMessageBox::information(this, tr("Torrent creator")
//        , QString("%1\n%2").arg(tr("Torrent created:"), Utils::Fs::toNativePath(path)));
    setInteractionEnabled(true);
}

void TorrentCreatorDialog::setInteractionEnabled(bool enabled)
{
    ui_->textInputPath->setEnabled(enabled);
    ui_->btnAddFile->setEnabled(enabled);
    ui_->btnAddFolder->setEnabled(enabled);
    ui_->Encrypt->setEnabled(enabled);
    ui_->Trackers->setEnabled(enabled);
    ui_->Options->setEnabled(enabled);
    ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enabled);
}
