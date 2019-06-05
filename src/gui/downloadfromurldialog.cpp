#include "downloadfromurldialog.h"
#include "ui_downloadfromurldialog.h"

#include <QClipboard>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QSet>
#include <QString>
#include <QStringList>

namespace
{
    bool isDownloadable(const QString &str)
    {
        return (str.startsWith("http://", Qt::CaseInsensitive)
            || str.startsWith("https://", Qt::CaseInsensitive)
            || str.startsWith("ftp://", Qt::CaseInsensitive)
            || str.startsWith("magnet:", Qt::CaseInsensitive)
            || str.startsWith("bc://bt/", Qt::CaseInsensitive)
            || ((str.size() == 40) && !str.contains(QRegularExpression("[^0-9A-Fa-f]")))
            || ((str.size() == 32) && !str.contains(QRegularExpression("[^2-7A-Za-z]"))));
    }
}

DownloadFromURLDialog::DownloadFromURLDialog(QWidget* parent)
    : QDialog{parent}
    , ui_{new Ui::DownloadFromURLDialog}
{
    ui_->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);

    ui_->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Download"));
    connect(ui_->buttonBox, &QDialogButtonBox::accepted, this, &DownloadFromURLDialog::downloadButtonClicked);
    connect(ui_->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    ui_->textURLs->setWordWrapMode(QTextOption::NoWrap);

    // Paste clipboard if there is an URL in it
    const QStringList clipboardList = qApp->clipboard()->text().split('\n');

    QSet<QString> uniqueURLs;
    for (QString str : clipboardList) {
        str = str.trimmed();
        if (str.isEmpty()) continue;

        if (isDownloadable(str))
            uniqueURLs << str;
    }
    ui_->textURLs->setText(uniqueURLs.toList().join('\n'));
    show();
}

DownloadFromURLDialog::~DownloadFromURLDialog()
{
    delete ui_;
}

void DownloadFromURLDialog::downloadButtonClicked()
{
    const QStringList urls = ui_->textURLs->toPlainText().split('\n');

    QSet<QString> uniqueURLs;
    for (QString url : urls) {
        url = url.trimmed();
        if (url.isEmpty()) continue;

        uniqueURLs << url;
    }

    if (uniqueURLs.isEmpty()) {
        QMessageBox::warning(this, tr("No URL entered"), tr("Please type at least one URL."));
        return;
    }

    emit urlsReadyToBeDownloaded(uniqueURLs.toList());
    accept();
}
