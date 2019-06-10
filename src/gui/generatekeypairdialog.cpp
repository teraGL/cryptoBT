#include "generatekeypairdialog.h"
#include "ui_generatekeypairdialog.h"

#include <QLineEdit>
#include <QRegularExpression>
#include <QTemporaryFile>

GenerateKeyPairDialog::GenerateKeyPairDialog(QWidget* parent)
    : QDialog{parent}
    , ui_{new Ui::GenerateKeyPairDialog}
{
    ui_->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);

    QString welcome_text("<h2><center><b>Welcome to cryptoBT 0.0.1</b></center></h2><br>"
                               "<p>cryptoBT needs private key and public key (certificate) for actions,<br>"
                               "when you create torrent file or decrypt downloaded torrent file content.</p>"
                               "<ul><li>The private key is needed to decrypt or sign.</li>"
                               "<li>The public key can be used by others to encrypt to you or verify your indentity.</li></ul>");
    ui_->label->setText(welcome_text);

    welcome_text = "<b>Enter Details</b>"
                   "<p>Please enter your personal details below.</p>";
    ui_->label_4->setText(welcome_text);
    ui_->InfoAboutGenerationKeys->setText("The process of creating a key requires large amounts of random numbers.<br>"
                                          "This may require several minutes...");

    ui_->statusLinesEdit->setStyleSheet("QLabel { color: red }");
    ui_->plainTextEdit->setReadOnly(true);

    // singnal/slot connections
    connect(ui_->btnNewKeyPair, &QPushButton::clicked, this, &GenerateKeyPairDialog::onNewKeyPairButtonClicked);
    connect(ui_->nameLineEdit, &QLineEdit::textEdited, this, &GenerateKeyPairDialog::checkCorrectFills);
    connect(ui_->emailLineEdit, &QLineEdit::textEdited, this, &GenerateKeyPairDialog::checkCorrectFills);

    connect(ui_->btnNext, &QPushButton::clicked, this, &GenerateKeyPairDialog::onNextButtonClicked);
    connect(ui_->btnBackFromReview, &QPushButton::clicked, this, &GenerateKeyPairDialog::onBackFromReviewButtonClicked);
    connect(ui_->btnCreate, &QPushButton::clicked, this, &GenerateKeyPairDialog::onCreateButtonClicked);

    // closing form
    connect(ui_->btnCancelFromFillData, &QPushButton::clicked, this, &GenerateKeyPairDialog::close);
    connect(ui_->btnCancelFromReview, &QPushButton::clicked, this, &GenerateKeyPairDialog::close);
    connect(ui_->btnCancelCreatingKeyPair, &QPushButton::clicked, this, &GenerateKeyPairDialog::close);
}

GenerateKeyPairDialog::~GenerateKeyPairDialog()
{
    delete ui_;
}

void GenerateKeyPairDialog::onNewKeyPairButtonClicked()
{
    ui_->stackedWidget->setCurrentIndex(1);

    ui_->btnNext->setEnabled(false);
    ui_->btnBackDisabled->setEnabled(false);
}

void GenerateKeyPairDialog::checkCorrectFills()
{
    if (ui_->nameLineEdit->text().length() < 6) {
        ui_->statusLinesEdit->setText("<i>Name</i> is incomplete.");
    }
    else {
        const QRegularExpression email_regex(
            "^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$"
        );
        if (!email_regex.match(ui_->emailLineEdit->text()).hasMatch()) {
            ui_->statusLinesEdit->setText("<i>Email</i> is incomplete.");
        } else {
            ui_->statusLinesEdit->setText("");
            ui_->btnNext->setEnabled(true);
        }
    }
}

void GenerateKeyPairDialog::onNextButtonClicked()
{
    ui_->stackedWidget->setCurrentIndex(2);

    const QString content_file = QString(
                "Name:            %1\n"
                "Email Address:   %2\n"
                "Key Type:        RSA\n"
                "Key Strength:    4096\n"
                "Subkey Type:     RSA\n"
                "Subkey Strength: 4096"
    ).arg(ui_->nameLineEdit->text()).arg(ui_->emailLineEdit->text());

    ui_->plainTextEdit->setPlainText(content_file);
}

void GenerateKeyPairDialog::onBackFromReviewButtonClicked()
{
    ui_->stackedWidget->setCurrentIndex(1);
}

void GenerateKeyPairDialog::onCreateButtonClicked()
{
    ui_->stackedWidget->setCurrentIndex(3);
    ui_->stackedWidget->repaint();
    generateKeys();
}

void GenerateKeyPairDialog::generateKeys()
{
    const QString content_file = QString(
                "Key-Type: RSA\n"
                "Key-Length: 4096\n"
                "Subkey-Type: RSA\n"
                "Subkey-Length: 4096\n"
                "Name-Real: %1\n"
                "Name-Email: %2\n"
                "Expire-Date: 0"
    ).arg(ui_->nameLineEdit->text()).arg(ui_->emailLineEdit->text());

    QTemporaryFile tmpUserInfo;
    QString tmpName;

    if (tmpUserInfo.open()) {
        tmpName = tmpUserInfo.fileName();
        tmpUserInfo.write(content_file.toStdString().c_str());
        tmpUserInfo.flush();
    }

    const QString commandGenKey = QString("gpg --batch --gen-key %1").arg(tmpName);
    system(commandGenKey.toStdString().c_str());

    //TODO 1: Create last stack window for displaying generated information
    //TODO 2: Implemet class GpgInfo for (importing pubkeys or fingerprints), and use in windows button, like export
    //TODO 3: Show list of public keys, maybe display: [ name + email + fingerprint ]
}
