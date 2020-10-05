#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/guiResources/background/background2.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(960,560);
    QWidget::setWindowTitle ("Rubber Contract Bridge");
    ui->clientButton->setIcon(QIcon(":/resources/guiResources/background/clientButton2.png"));
    ui->serverButton->setIcon(QIcon(":/resources/guiResources/background/serverButton2.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clientButton_clicked()
{
    this->close();
    clientWindow = new clientGUI();
    clientWindow->show();

}

void MainWindow::on_serverButton_clicked()
{
    this->close();
    serverWindow = new serverGUI();
    serverWindow->show();
}
