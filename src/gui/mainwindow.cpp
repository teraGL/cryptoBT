#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    setWindowTitle("cryptoBT");
    setWindowIcon(QIcon(":/icons/logo.png"));
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::about()
{
    QLabel *icon = new QLabel;
    icon->setPixmap(QPixmap(":/icons/logo.png"));

    QLabel *text = new QLabel;
    text->setWordWrap(true);
    text->setText("<h2>crytoBT 0.0.1</h2>"
                  "<p>A secure and easy BitTorrent Client programmed in C++,"
                  " based on Qt toolkit, crypto++ and libtorrent-rasterbar.</p>");

    QPushButton *quitButton = new QPushButton("OK");

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setMargin(10);
    topLayout->setSpacing(10);
    topLayout->addWidget(icon);
    topLayout->addWidget(text);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(quitButton);
    bottomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    QDialog about(this);
    about.setModal(true);
    about.setWindowTitle(tr("About cryptBT"));
    about.setLayout(mainLayout);
    about.layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(quitButton, &QPushButton::clicked, &about, &QDialog::close);

    about.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    about();
}
