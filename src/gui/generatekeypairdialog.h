#ifndef GENERATEKEYPAIRDIALOG_H
#define GENERATEKEYPAIRDIALOG_H

#include <QDialog>

namespace Ui
{
    class GenerateKeyPairDialog;
}

class GenerateKeyPairDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateKeyPairDialog(QWidget* parent = nullptr);
    ~GenerateKeyPairDialog();

private slots:
    void onNewKeyPairButtonClicked();
    void onCreateButtonClicked();

private:
    void createPassphrase();
    void generateKeys();

    Ui::GenerateKeyPairDialog* ui_;
    QString name_;
    QString email_;
    QString passwd_;
};

#endif // GENERATEKEYPAIRDIALOG_H
