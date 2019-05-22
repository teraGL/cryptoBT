#ifndef ENCRYPTORTHREAD_H
#define ENCRYPTORTHREAD_H

#include <QThread>

class EncryptorThread : public QThread
{
    Q_OBJECT

public:
    EncryptorThread(QObject* parent = nullptr);
//    ~EncryptorThread();

//    void create(const );
//protected:
//    void run();

//signals:
//    void creationFailure(const QString& msg);
//    void creationSuccess(const QString &path, const QString &branchPath);
//    void updateProgress(int progress);

//private:
//    void sendProgressSignal(int currentPieceIdx, int totalPieces);
};

#endif // ENCRYPTORTHREAD_H
