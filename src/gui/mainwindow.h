#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

namespace Ui
{
    class MainWindow;
}

class TorrentCreatorDialog;
class DownloadFromURLDialog;
class AddTorrentFileDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void createKeyboardShortcuts();
    void downloadFromURLList(const QStringList &urlList);
    void about();

    void on_actionAbout_triggered();
    void on_actionCreateNewTorrent_triggered();
    void on_actionAddTorrentLink_triggered();
    void on_actionExit_triggered();

    void on_actionAddTorrentFile_triggered();

private:
    Ui::MainWindow* ui_;
    QPointer<TorrentCreatorDialog> torrent_creator_dlg_;
    QPointer<DownloadFromURLDialog> download_from_URL_dlg_;
    QPointer<AddTorrentFileDialog> add_torrent_file_dlg_;
};

#endif // MAINWINDOW_H
