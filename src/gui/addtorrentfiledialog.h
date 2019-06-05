#ifndef ADDTORRENTFILEDIALOG_H
#define ADDTORRENTFILEDIALOG_H

#include <QDialog>

namespace Ui
{
    class AddTorrentFileDialog;
}

class AddTorrentFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTorrentFileDialog(QWidget* parent = nullptr, const QString& torrentFile = {});
    ~AddTorrentFileDialog();

private slots:
    void onSourcePathChanged();
    void onDestinationPathChanged();

private:
    QString getSourceFileName(const QString& filename) const;
    QString getDestinationFolderName(const QString &foldername) const;

    QString getTorrentSize() const;
    QString getTorrentDate() const;
    QString getTorrentHash() const;
    QString getTorrentComment() const;

    Ui::AddTorrentFileDialog* ui_;
    QString torrent_file_;
};

#endif // ADDTORRENTFILEDIALOG_H
