#ifndef DOWNLOADFROMURLDIALOG_H
#define DOWNLOADFROMURLDIALOG_H

#include <QDialog>

namespace Ui
{
    class DownloadFromURLDialog;
}

class DownloadFromURLDialog : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(DownloadFromURLDialog)

public:
    explicit DownloadFromURLDialog(QWidget* parent = nullptr);
    ~DownloadFromURLDialog();

signals:
    void urlsReadyToBeDownloaded(const QStringList &torrentURLs);

private slots:
    void downloadButtonClicked();

private:
    Ui::DownloadFromURLDialog* ui_;
};

#endif // DOWNLOADFROMURLDIALOG_H
