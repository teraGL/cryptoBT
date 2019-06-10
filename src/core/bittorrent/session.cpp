//#include "session.h"

//#include <libtorrent/alert_types.hpp>
//#include <libtorrent/bdecode.hpp>
//#include <libtorrent/bencode.hpp>
//#include <libtorrent/disk_io_thread.hpp>
//#include <libtorrent/error_code.hpp>
//#include <libtorrent/extensions/ut_metadata.hpp>
//#include <libtorrent/extensions/ut_pex.hpp>
//#include <libtorrent/extensions/smart_ban.hpp>
//#include <libtorrent/identify_client.hpp>
//#include <libtorrent/ip_filter.hpp>
//#include <libtorrent/magnet_uri.hpp>
//#include <libtorrent/session.hpp>
//#include <libtorrent/session_stats.hpp>
//#include <libtorrent/session_status.hpp>
//#include <libtorrent/torrent_info.hpp>
//#include <libtorrent/version.hpp>

//#include <QDir>

//using namespace BitTorrent;

//Session* Session::instance_ = nullptr;

//Session::Session(QObject* parent)
//    : QObject{parent}
//{
//    initResumeFolder();

//    // Set severity level of libtorrent session
//    const int alertMask = lt::alert::error_notification
//                        | lt::alert::port_mapping_notification
//                        | lt::alert::storage_notification
//                        | lt::alert::tracker_notification
//                        | lt::alert::status_notification
//                        | lt::alert::ip_block_notification
//                        | lt::alert::file_progress_notification
//                        | lt::alert::stats_notification;

//    lt::settings_pack pack;
//    pack.set_int(lt::settings_pack::alert_mask, alertMask);
//    pack.set_bool(lt::settings_pack::listen_system_port_fallback, false);
//    pack.set_bool(lt::settings_pack::use_dht_as_fallback, false);
//    // Disable support for SSL torrents for now
//    pack.set_int(lt::settings_pack::ssl_listen, 0);
//    // To prevent ISPs from blocking seeding
//    pack.set_bool(lt::settings_pack::lazy_bitfields, true);
//    // Speed up exit
//    pack.set_int(lt::settings_pack::stop_tracker_timeout, 1);
//    pack.set_int(lt::settings_pack::auto_scrape_interval, 1200); // 20 minutes
//    pack.set_int(lt::settings_pack::auto_scrape_min_interval, 900); // 15 minutes
//    pack.set_int(lt::settings_pack::connection_speed, 20); // default is 10
//    pack.set_bool(lt::settings_pack::no_connect_privileged_ports, false);
//    pack.set_bool(lt::settings_pack::use_disk_cache_pool, false);

//    pack.set_bool(lt::settings_pack::enable_upnp, true);
//    pack.set_bool(lt::settings_pack::enable_natpmp, true);
//    pack.set_bool(lt::settings_pack::upnp_ignore_nonrouters, true);
//    pack.set_bool(lt::settings_pack::allow_multiple_connections_per_ip, true);
//    pack.set_bool(lt::settings_pack::enable_dht, true);
//    pack.set_str(lt::settings_pack::dht_bootstrap_nodes, "dht.libtorrent.org:25401,router.bittorrent.com:6881,router.utorrent.com:6881,dht.transmissionbt.com:6881,dht.aelitis.com:6881");
//    pack.set_bool(lt::settings_pack::enable_lsd, true);

//    native_session_ = new lt::session {pack, int{0}};

//    // Enabling plugins
//    native_session_->add_extension(&lt::create_ut_metadata_plugin);
//    native_session_->add_extension(&lt::create_ut_pex_plugin);
//    qDebug("* BitTorrent Session constructed");
//}

//void Session::initResumeFolder()
//{
////    resume_folder_path_ = Utils::Fs::expandPathAbs(specialFolderLocation(SpecialFolder::Data) + RESUME_FOLDER);
////    const QDir resumeFolderDir(resume_folder_path_);
////    if (resumeFolderDir.exists() || resumeFolderDir.mkpath(resumeFolderDir.absolutePath())) {
////        resumeFolderLock.setFileName(resumeFolderDir.absoluteFilePath("session.lock"));
////        if (!m_resumeFolderLock.open(QFile::WriteOnly)) {
////            throw RuntimeError {tr("Cannot write to torrent resume folder.")};
////        }
////    }
////    else {
////        throw RuntimeError {tr("Cannot create torrent resume folder.")};
////    }
//}
