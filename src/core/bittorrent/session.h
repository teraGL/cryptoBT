#ifndef SESSION_H
#define SESSION_H

#include <QPointer>
#include <QFile>

#include "addtorrentparams.h"
#include "torrentinfo.h"
#include "sessionstatus.h"

#include <libtorrent/session.hpp>

namespace BitTorrent
{

class AddTorrentParams;
class SessionStatus;

class Session : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Session)

public:
    static void initInstance();
    static void freeInstance();
    static Session* instance();

    QString defaultSavePath() const;
    void setDefaultSavePath(QString path);

    bool addTorrent(const QString &source, const AddTorrentParams &params = AddTorrentParams());
    bool addTorrent(const TorrentInfo &torrentInfo, const AddTorrentParams &params = AddTorrentParams());
    bool deleteTorrent(const QString &hash, bool deleteLocalFiles = false);

    int downloadSpeedLimit() const;
    void setDownloadSpeedLimit(int limit);
    int uploadSpeedLimit() const;
    void setUploadSpeedLimit(int limit);

    bool hasActiveTorrents() const;
    bool hasUnfinishedTorrents() const;
    bool hasRunningSeed() const;


private:
    explicit Session(QObject* parent = nullptr);
    ~Session();

    void initResumeFolder();

    // BitTorrent
    libtorrent::session* native_session_;

    QString resume_folder_path_;

    SessionStatus status_;

    static Session* instance_;
};

} // BitTorrent

#endif // SESSION_H
