//#ifndef TRANSFERLISTMODEL_H
//#define TRANSFERLISTMODEL_H

//#include <QAbstractListModel>
//#include <QList>

//namespace BitTorrent
//{
//    class InfoHash;
//    class TorrentHandle;
//}

//class TransferListModel : public QAbstractListModel
//{
//    Q_OBJECT
//    Q_DISABLE_COPY(TransferListModel)

//public:
//    enum
//    {
//        TR_PRIORITY,
//        TR_NAME,
//        TR_SIZE,
//        TR_TOTAL_SIZE,
//        TR_PROGRESS,
//        TR_STATUS,
//        TR_SEEDS,
//        TR_PEERS,
//        TR_DLSPEED,
//        TR_UPSPEED,
//        TR_ETA,
//        TR_RATIO,
//        TR_CATEGORY,
//        TR_TAGS,
//        TR_ADD_DATE,
//        TR_SEED_DATE,
//        TR_TRACKER,
//        TR_DLLIMIT,
//        TR_UPLIMIT,
//        TR_AMOUNT_DOWNLOADED,
//        TR_AMOUNT_UPLOADED,
//        TR_AMOUNT_DOWNLOADED_SESSION,
//        TR_AMOUNT_UPLOADED_SESSION,
//        TR_AMOUNT_LEFT,
//        TR_TIME_ELAPSED,
//        TR_SAVE_PATH,
//        TR_COMPLETED,
//        TR_RATIO_LIMIT,
//        TR_SEEN_COMPLETE_DATE,
//        TR_LAST_ACTIVITY,

//        NB_COLUMNS
//    };

//    explicit TransferListModel(QObject* parent = nullptr);

//    int rowCount(const QModelIndex& index = {}) const override;
//    int columnCount(const QModelIndex& parent=QModelIndex()) const override;
//    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
//    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
//    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
//    Qt::ItemFlags flags(const QModelIndex& index) const override;

//    BitTorrent::TorrentHandle *torrentHandle(const QModelIndex &index) const;

//private slots:
//    void addTorrent(BitTorrent::TorrentHandle *const torrent);
//    void handleTorrentAboutToBeRemoved(BitTorrent::TorrentHandle *const torrent);
//    void handleTorrentStatusUpdated(BitTorrent::TorrentHandle *const torrent);
//    void handleTorrentsUpdated();

//private:
//    QList<BitTorrent::TorrentHandle *> torrents_;
//};

//#endif // TRANSFERLISTMODEL_H
