#ifndef TORRENTCREATORDIALOG_H
#define TORRENTCREATORDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui
{
    class TorrentCreatorDialog;
}

class TorrentCreatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TorrentCreatorDialog(QWidget* parent = nullptr, const QString& defaultPath = {});
    ~TorrentCreatorDialog();
    void updateInputPath(const QString& path);

private slots:
    void onAddFileButtonClicked();
    void onAddFolderButtonClicked();
    void onCreateButtonClicked();
    void handleCreationFailure(const QString &msg);
    void handleCreationSuccess(const QString &path, const QString &branchPath);

private:
//    void saveSettings();
//    void loadSettings();
//    int getPieceSize() const;
    void setInteractionEnabled(bool enabled);

    Ui::TorrentCreatorDialog* ui_;
    QString filename_;
};

QString createDefaultSeedingDir(const QString& filepath);

#endif // TORRENTCREATORDIALOG_H
