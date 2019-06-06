#include "torrentcreatordialog.h"
#include "ui_torrentcreatordialog.h"

#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>

#include "crypto/blockcryptor.h"

#include "core/bittorrent/session.h"
#include "core/bittorrent/torrentcreatorthread.h"
#include "core/bittorrent/torrentinfo.h"

TorrentCreatorDialog::TorrentCreatorDialog(QWidget* parent, const QString& defautPath)
    : QDialog{parent}
    , ui_{new Ui::TorrentCreatorDialog}
    , creatorThread_{new BitTorrent::TorrentCreatorThread(this)}
    , model_{new QStringListModel(this)}
{
    ui_->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(false);

    ui_->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Create Torrent"));
    ui_->pubKeysView->setModel(model_);
    ui_->pubKeysView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui_->btnAddFile, &QPushButton::clicked, this, &TorrentCreatorDialog::onAddFileButtonClicked);
    connect(ui_->btnAddFolder, &QPushButton::clicked, this, &TorrentCreatorDialog::onAddFolderButtonClicked);
    connect(ui_->btnChoose, &QPushButton::clicked, this, &TorrentCreatorDialog::onChooseButtonClicked);
    connect(ui_->buttonBox, &QDialogButtonBox::accepted, this, &TorrentCreatorDialog::onCreateButtonClicked);
    connect(ui_->buttonBox, &QDialogButtonBox::rejected, this, &TorrentCreatorDialog::close);

    connect(creatorThread_, &BitTorrent::TorrentCreatorThread::creationSuccess, this, &TorrentCreatorDialog::handleCreationSuccess);
    connect(creatorThread_, &BitTorrent::TorrentCreatorThread::creationFailure, this, &TorrentCreatorDialog::handleCreationFailure);
    connect(creatorThread_, &BitTorrent::TorrentCreatorThread::updateProgress, this, &TorrentCreatorDialog::updateProgressBarTorrent);

    loadSettings();
    updateInputPath(defautPath);

    show();
}

TorrentCreatorDialog::~TorrentCreatorDialog()
{
    qDebug() << "Removed TorrentCreatorDialog...";
    saveSettings();
    delete ui_;
}

void TorrentCreatorDialog::updateInputPath(const QString &path)
{
    if (path.isEmpty()) return;
    ui_->textInputPath->setText(QDir::toNativeSeparators(path));
}

void TorrentCreatorDialog::updateProgressBarEncryption(int progress)
{
    ui_->progressBarEncrypting->setValue(progress);
}

void TorrentCreatorDialog::updateProgressBarTorrent(int progress)
{
    ui_->progressBarTorrent->setValue(progress);
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

void TorrentCreatorDialog::onChooseButtonClicked()
{
    const QStringList fullPathPubKeys = QFileDialog::getOpenFileNames(
                this, tr("Choose public keys"), QDir::homePath());

    QStringList pubkeys;
    QString filename;
    for (const auto pb : fullPathPubKeys) {
        filename = pb.split("/").last();
        pubkeys.append(filename);
    }
    model_->setStringList(pubkeys);
}

void TorrentCreatorDialog::onCreateButtonClicked()
{
    input_ = QDir::fromNativeSeparators(ui_->textInputPath->text()).trimmed();

    // test if readable
    const QFileInfo fi(input_);
    if (!fi.isReadable()) {
        QMessageBox::critical(this, tr("Torrent creation failed"), tr("Reason: Path to file/folder is not readable."));
        return;
    }
    input_ = fi.canonicalFilePath();

    if (model_->rowCount() == 0) {
        QMessageBox::critical(this, tr("Torrent creation failed"), tr("Reason: No public key selected."));
        return;
    }

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

    // Encrypting files
    const int algorithm_index = ui_->comboBoxAlgorithm->currentIndex();
    const size_t key_size = ui_->comboBoxKeySize->currentText().toInt();

    BlockCryptor encryptor;
    switch (algorithm_index) {
        case 0:  encryptor.setCipher<AesCipher>(key_size);       break;
        case 1:  encryptor.setCipher<TwofishCipher>(key_size);   break;
        case 2:  encryptor.setCipher<SerpentCipher>(key_size);   break;
        case 3:  encryptor.setCipher<CamelliaCipher>(key_size);  break;
    }

    // TODO: implement the way of displaying process of encryption
    encryptor.generateKey();
    ui_->progressBarEncrypting->setValue(2);

    encryptor.saveSecretKey(input_);
    ui_->progressBarEncrypting->setValue(4);

    encryptor.encryptFile(input_);
    ui_->progressBarEncrypting->setValue(100);


    // Creating torrent file
    const QString seeding_dir = createDirForFileWithKey(input_);
    input_ = seeding_dir;
    qDebug() << "Output file: " << input_;

    const QStringList trackers = ui_->textTrackersURLs->toPlainText().trimmed()
        .replace(QRegularExpression("\n\n[\n]+"), "\n\n").split('\n');
    const QString comment = ui_->lineComment->text();

    creatorThread_->create({ ui_->checkBoxPrivateTorrent->isChecked(), getPieceSize(),
                             input_, destination, comment, trackers });
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
    if (ui_->checkBoxStartSeeding->isChecked()) {
        QMessageBox::information(this, tr("seeding checkbox"), tr("Start seeding immediately"));
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
    }
    QMessageBox::information(this, tr("Torrent creator")
        , QString("%1\n%2").arg(tr("Torrent created:"), QDir::toNativeSeparators(path)));
    setInteractionEnabled(true);
}

void TorrentCreatorDialog::saveSettings()
{

}

void TorrentCreatorDialog::loadSettings()
{

}

int TorrentCreatorDialog::getPieceSize() const
{
    const int pieceSizes[] = {0, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};  // base unit in KiB
    return pieceSizes[ui_->comboBoxPieceSize->currentIndex()] * 1024;
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

QString createDefaultSeedingDir()
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

    return seeding_dir;
}

QString createDirForFileWithKey(const QString& dirname)
{
    const QString outDir = createDefaultSeedingDir() + QFileInfo(dirname).fileName() + "/";
    if (!QDir(outDir).exists()) {
        QDir().mkpath(outDir);
        qDebug() << "Created '~/Documents/cryptBT/Seeding/'" << outDir << "successfully!\n";
    }
    return outDir;
}
