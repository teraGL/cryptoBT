//#include "transferlistmodel.h"

//#include <QApplication>
//#include <QDateTime>
//#include <QDebug>
//#include <QIcon>
//#include <QPalette>

//#include "core/bittorrent/session.h"
////#include "core/bittorrent/torrenthandle.h"


//TransferListModel::TransferListModel(QObject* parent)
//    : QAbstractListModel{parent}
//{
//    // Load the torrents
//    using namespace BitTorrent;
//    for (TorrentHandle *const torrent : Session::instance()->torrents())
//        addTorrent(torrent);

//    // Listen for torrent changes
//    connect(Session::instance(), &Session::torrentAdded, this, &TransferListModel::addTorrent);
//    connect(Session::instance(), &Session::torrentAboutToBeRemoved, this, &TransferListModel::handleTorrentAboutToBeRemoved);
//    connect(Session::instance(), &Session::torrentsUpdated, this, &TransferListModel::handleTorrentsUpdated);

//    connect(Session::instance(), &Session::torrentFinished, this, &TransferListModel::handleTorrentStatusUpdated);
//    connect(Session::instance(), &Session::torrentMetadataLoaded, this, &TransferListModel::handleTorrentStatusUpdated);
//    connect(Session::instance(), &Session::torrentResumed, this, &TransferListModel::handleTorrentStatusUpdated);
//    connect(Session::instance(), &Session::torrentPaused, this, &TransferListModel::handleTorrentStatusUpdated);
//    connect(Session::instance(), &Session::torrentFinishedChecking, this, &TransferListModel::handleTorrentStatusUpdated);
//}
