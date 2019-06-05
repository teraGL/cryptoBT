#include "torrentcreatorthread.h"

#include <fstream>

#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/storage.hpp>
#include <libtorrent/create_torrent.hpp>
#include <libtorrent/version.hpp>

#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QHash>

namespace lt = libtorrent;
using namespace BitTorrent;

namespace
{
    using CreateFlags = int;//lt::create_flags_t;

    // do not include files and folders whose
    // name starts with a .
    bool fileFilter(const std::string& f)
    {
        const QString path = QDir::fromNativeSeparators(QString::fromStdString(f));
        const int slashIndex = path.lastIndexOf('/');
        QString fileName = (slashIndex == -1) ? path : path.mid(slashIndex + 1);
        return !fileName.startsWith('.');
    }

    QString branchPath(const QString& filePath, QString* removed = nullptr)
    {
        QString ret = QDir::fromNativeSeparators(filePath);
        if (ret.endsWith('/'))
            ret.chop(1);
        const int slashIndex = ret.lastIndexOf('/');
        if (slashIndex >= 0) {
            if (removed)
                *removed = ret.mid(slashIndex + 1);
            ret = ret.left(slashIndex);
        }
        return ret;
    }
}


TorrentCreatorThread::TorrentCreatorThread(QObject* parent)
    : QThread{parent}
{
}

TorrentCreatorThread::~TorrentCreatorThread()
{
    requestInterruption();
    wait();
}

void TorrentCreatorThread::create(const TorrentCreatorParams& params)
{
    params_ = params;
    start();
}

void TorrentCreatorThread::sendProgressSignal(int currentPieceIdx, int totalPieces)
{
    emit updateProgress(static_cast<int>((currentPieceIdx * 100.0) / totalPieces));
}

void TorrentCreatorThread::run()
{
    const QString creatorStr("cryptoBT 0.0.1");

    emit updateProgress(0);

    try {
        const QString parentPath = branchPath(params_.input_path) + '/';

        // Adding files to the torrent
        lt::file_storage fs;
        if (QFileInfo(params_.input_path).isFile()) {
            lt::add_files(fs, QDir::toNativeSeparators(params_.input_path).toStdString(), fileFilter);
        }
        else {
            // need to sort the file names by natural sort order
            QStringList dirs = {params_.input_path};

            QDirIterator dirIter(params_.input_path, (QDir::AllDirs | QDir::NoDotAndDotDot), QDirIterator::Subdirectories);
            while (dirIter.hasNext()) {
                dirIter.next();
                dirs += dirIter.filePath();
            }
//            std::sort(dirs.begin(), dirs.end(), Utils::String::naturalLessThan<Qt::CaseInsensitive>);
            std::sort(dirs.begin(), dirs.end());

            QStringList fileNames;
            QHash<QString, qint64> fileSizeMap;

            for (const auto &dir : dirs) {
                QStringList tmpNames;  // natural sort files within each dir

                QDirIterator fileIter(dir, QDir::Files);
                while (fileIter.hasNext()) {
                    fileIter.next();

                    const QString relFilePath = fileIter.filePath().mid(parentPath.length());
                    tmpNames += relFilePath;
                    fileSizeMap[relFilePath] = fileIter.fileInfo().size();
                }

//                std::sort(tmpNames.begin(), tmpNames.end(), Utils::String::naturalLessThan<Qt::CaseInsensitive>);
                std::sort(tmpNames.begin(), tmpNames.end());
                fileNames += tmpNames;
            }

            for (const auto &fileName : fileNames)
                fs.add_file(fileName.toStdString(), fileSizeMap[fileName]);
        }

        if (isInterruptionRequested()) return;

        lt::create_torrent newTorrent(fs, params_.piece_size, -1, CreateFlags{});

        int tier = 0;
        for (const QString &tracker : params_.trackers) {
            if (tracker.isEmpty())
                ++tier;
            else
                newTorrent.add_tracker(tracker.trimmed().toStdString(), tier);
        }

        if (isInterruptionRequested()) return;

        // calculate the hash for all pieces
        lt::set_piece_hashes(newTorrent, QDir::toNativeSeparators(parentPath).toStdString()
            , [this, &newTorrent](const int n) { sendProgressSignal(n, newTorrent.num_pieces()); });
        // Set qBittorrent as creator and add user comment to
        // torrent_info structure
        newTorrent.set_creator(creatorStr.toUtf8().constData());
        newTorrent.set_comment(params_.comment.toUtf8().constData());
        // Is private ?
        newTorrent.set_priv(params_.isPrivate);

        if (isInterruptionRequested()) return;

        lt::entry entry = newTorrent.generate();

        if (isInterruptionRequested()) return;

        // create the torrent
        std::ofstream outfile(
            QDir::toNativeSeparators(params_.save_path).toUtf8().constData()
                                    , (std::ios_base::out | std::ios_base::binary | std::ios_base::trunc)
        );

        if (outfile.fail())
            throw std::runtime_error(tr("create new torrent file failed").toStdString());

        if (isInterruptionRequested()) return;

        lt::bencode(std::ostream_iterator<char>(outfile), entry);
        outfile.close();

        emit updateProgress(100);
        emit creationSuccess(params_.save_path, parentPath);
    }
    catch (const std::exception &e) {
        emit creationFailure(e.what());
    }
}

int TorrentCreatorThread::calculateTotalPieces(const QString &inputPath, const int pieceSize)
{
    if (inputPath.isEmpty())
        return 0;

    lt::file_storage fs;
    lt::add_files(fs, QDir::toNativeSeparators(inputPath).toStdString(), fileFilter);

    return lt::create_torrent(fs, pieceSize, -1,CreateFlags{}).num_pieces();
}
