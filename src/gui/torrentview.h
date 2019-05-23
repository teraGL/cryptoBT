#ifndef TORRENTVIEW_H
#define TORRENTVIEW_H

#include <QListView>

class TorrentView : public QListView
{
    Q_OBJECT

public:
    TorrentView(QWidget* parent = nullptr);

};

#endif // TORRENTVIEW_H
