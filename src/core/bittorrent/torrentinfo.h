#ifndef TORRENTINFO_H
#define TORRENTINFO_H

#include <libtorrent/torrent_info.hpp>
#include <libtorrent/version.hpp>

namespace BitTorrent
{

class InfoHash;
class TrackerEntry;

class TorrentInfo
{
public:
    TorrentInfo();
};

} // BitTorrent

#endif // TORRENTINFO_H
