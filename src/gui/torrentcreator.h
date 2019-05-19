#ifndef TORRENTCREATOR_H
#define TORRENTCREATOR_H

#include <QDialog>

namespace Ui
{
    class TorrentCreator;
}

class TorrentCreator : public QDialog
{
    Q_OBJECT

public:
    explicit TorrentCreator(QWidget* parent = nullptr);
    ~TorrentCreator();

private:
    Ui::TorrentCreator* ui_;
};

#endif // TORRENTCREATOR_H
