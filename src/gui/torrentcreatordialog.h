#ifndef TORRENTCREATORDIALOG_H
#define TORRENTCREATORDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringListModel>

namespace Ui
{
    class TorrentCreatorDialog;
}

namespace BitTorrent
{
    class TorrentCreatorThread;
}

class TorrentCreatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TorrentCreatorDialog(QWidget* parent = nullptr, const QString& defaultPath = {});
    ~TorrentCreatorDialog() override;
    void updateInputPath(const QString& path);

private slots:
    void updateProgressBarEncryption(int progress);
    void updateProgressBarTorrent(int progress);
    void onAddFileButtonClicked();
    void onAddFolderButtonClicked();
    void onChooseButtonClicked();
    void onCreateButtonClicked();
    void handleCreationFailure(const QString &msg);
    void handleCreationSuccess(const QString &path, const QString &branchPath);

private:
    void saveSettings();
    void loadSettings();
    int getPieceSize() const;
    void setInteractionEnabled(bool enabled);

    Ui::TorrentCreatorDialog* ui_;
    BitTorrent::TorrentCreatorThread* creatorThread_;
    QStringListModel* model_;
    QString input_;
};

#endif // TORRENTCREATORDIALOG_H
