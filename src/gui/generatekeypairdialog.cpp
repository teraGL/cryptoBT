#include "generatekeypairdialog.h"
#include "ui_generatekeypairdialog.h"

#include <QMessageBox>
#include <QRegularExpression>
#include <QLineEdit>

#include <cstdlib>

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
    ui_->passwdLineEdit->setEchoMode(QLineEdit::Password);

    connect(ui_->btnNewKeyPair, &QPushButton::clicked, this, &GenerateKeyPairDialog::onNewKeyPairButtonClicked);
    connect(ui_->btnCreate, &QPushButton::clicked, this, &GenerateKeyPairDialog::onCreateButtonClicked);
}

GenerateKeyPairDialog::~GenerateKeyPairDialog()
{
    delete ui_;
}

void GenerateKeyPairDialog::onNewKeyPairButtonClicked()
{
    ui_->stackedWidget->setCurrentIndex(1);
    //TODO: Form with Passphrase
    //TODO: Form for Print result
}

void GenerateKeyPairDialog::onCreateButtonClicked()
{
    if (ui_->nameLineEdit->text().length() < 5) {
        QMessageBox::critical(this, tr("Creating fields"), tr("Reason: Name is too short."));
        return;
    }

    const QRegularExpression re("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    if (!re.match(ui_->emailLineEdit->text()).hasMatch()) {
        QMessageBox::critical(this, tr("Creating fields"), tr("Reason: Incorrect email address."));
        return;
    }

    if (ui_->passwdLineEdit->text().length() < 8) {
        QMessageBox::critical(this, tr("Creating fields"), tr("Reason: Password is too short."));
        return;
    }

    name_   = ui_->nameLineEdit->text();
    email_  = ui_->emailLineEdit->text();
    passwd_ = ui_->passwdLineEdit->text();


    generateKeys();
    createPassphrase();
}

void GenerateKeyPairDialog::createPassphrase()
{

}

void GenerateKeyPairDialog::generateKeys()
{

}
