#ifndef TORRENTCREATORTHREAD_H
#define TORRENTCREATORTHREAD_H

#include <QStringList>
#include <QThread>

namespace BitTorrent
{

struct TorrentCreatorParams
{
    bool isPrivate;
    int piece_size;
    QString input_path;
    QString save_path;
    QString comment;
    QStringList trackers;
};

class TorrentCreatorThread : public QThread
{
    Q_OBJECT

public:
    TorrentCreatorThread(QObject* parent = nullptr);
    ~TorrentCreatorThread();

    void create(const TorrentCreatorParams& params);
    static int calculateTotalPieces(const QString& inputPath, int pieceSize);

protected:
    void run();

signals:
    void creationFailure(const QString& msg);
    void creationSuccess(const QString& path, const QString& branchPath);
    void updateProgress(int progress);

private:
    void sendProgressSignal(int currentPieceIdx, int totalPieces);
    TorrentCreatorParams params_;
};

} // BitTorrent
#endif // TORRENTCREATORTHREAD_H
