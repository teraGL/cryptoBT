#include "addtorrentfiledialog.h"
#include "ui_addtorrentfiledialog.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>

AddTorrentFileDialog::AddTorrentFileDialog(QWidget* parent, const QString& torrentFile)
    : QDialog{parent}
    , ui_{new Ui::AddTorrentFileDialog}
    , torrent_file_{torrentFile}
{
    ui_->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(false);

    setWindowTitle("Add Torrent File");
    ui_->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Add"));
    ui_->buttonBox->button(QDialogButtonBox::Ok)->setIcon(QIcon(":/icons/add.svg"));

    ui_->btnFileSource->setStyleSheet("text-align:left;");
    ui_->btnFolderDest->setStyleSheet("text-align:left;");

    ui_->btnFileSource->setText(getSourceFileName(torrent_file_));
    ui_->btnFolderDest->setText(getDestinationFolderName(QStandardPaths::displayName(QStandardPaths::DownloadLocation)));

    connect(ui_->btnFileSource, &QPushButton::clicked, this, &AddTorrentFileDialog::onSourcePathChanged);
    connect(ui_->btnFolderDest, &QPushButton::clicked, this, &AddTorrentFileDialog::onDestinationPathChanged);

    ui_->sizeArg->setText(getTorrentSize());
    ui_->dateArg->setText("03/06/2019 19:44");
    ui_->hashArg->setText("jdf894joa8w4y93w4hf8394hf839w4hhuawhf934h");
    ui_->commentArg->setText("Hello, this is https://blackarch.org");

    show();
}

AddTorrentFileDialog::~AddTorrentFileDialog()
{
    delete ui_;
}

void AddTorrentFileDialog::onSourcePathChanged()
{
    const QString torrent_file = QFileDialog::getOpenFileName(this, tr("Choose torrent file"), QDir::homePath(), tr("Torrent Files (*.torrent)"));
    if (torrent_file.isEmpty())
        return;

    ui_->btnFileSource->setText(getSourceFileName(torrent_file));

    // Update Torrent Info data
    ui_->sizeArg->setText(getTorrentSize());
    ui_->dateArg->setText("22/12/2018 07:31");
    ui_->hashArg->setText("lasdjf82783938tyf7awsgfiaueyti4tyui");
    ui_->commentArg->setText("Hello, this is https://kali.org");
}

void AddTorrentFileDialog::onDestinationPathChanged()
{
    const QString dest_folder = QFileDialog::getExistingDirectory(this, tr("Choose destination folder"), QDir::homePath());
    if (dest_folder.isEmpty())
        return;

    ui_->btnFolderDest->setText(getDestinationFolderName(dest_folder));
}

QString AddTorrentFileDialog::getSourceFileName(const QString& filename) const
{
    return QFileInfo(filename).completeBaseName();
}

QString AddTorrentFileDialog::getDestinationFolderName(const QString& foldername) const
{
    return QDir(foldername).dirName();
}

QString AddTorrentFileDialog::getTorrentSize() const
{
    //TODO: torrent size for libtorrent-params
    return QLocale().formattedDataSize(QFile(torrent_file_).size(), 1);
}

QString AddTorrentFileDialog::getTorrentDate() const
{

}

QString AddTorrentFileDialog::getTorrentHash() const
{

}

QString AddTorrentFileDialog::getTorrentComment() const
{

}
