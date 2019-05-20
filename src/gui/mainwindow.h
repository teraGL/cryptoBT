#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

namespace Ui
{
    class MainWindow;
}

class TorrentCreatorDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void createKeyboardShortcuts();
    void about();

    void on_actionAbout_triggered();
    void on_actionCreateNewTorrent_triggered();

private:
    Ui::MainWindow* ui_;
    QPointer<TorrentCreatorDialog> torrent_creator_dlg_;
};

#endif // MAINWINDOW_H
