#include "torrentcreator.h"
#include "ui_torrentcreator.h"

TorrentCreator::TorrentCreator(QWidget* parent)
    : QDialog{parent}
    , ui_{new Ui::TorrentCreator}
{
    ui_->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

TorrentCreator::~TorrentCreator()
{
    delete ui_;
}
