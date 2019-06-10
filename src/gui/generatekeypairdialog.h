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
    void checkCorrectFills();
    void onNextButtonClicked();
    void onBackFromReviewButtonClicked();
    void onCreateButtonClicked();

private:
    void generateKeys();
    Ui::GenerateKeyPairDialog* ui_;
};

#endif // GENERATEKEYPAIRDIALOG_H
