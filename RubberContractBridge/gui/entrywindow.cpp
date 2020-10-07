#include "entrywindow.h"
#include "ui_entrywindow.h"

EntryWindow::EntryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EntryWindow)
{
    ui->setupUi(this);
    windowSetup();
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::windowSetup()
{
    QPixmap bkgnd(":/resources/guiResources/background/background2.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(415,520);
    QWidget::setWindowTitle ("Login Screen");
    ui->clientButton->setIcon(QIcon(":/resources/guiResources/background/unselectedButton.png"));
    ui->serverButton->setIcon(QIcon(":/resources/guiResources/background/unselectedButton.png"));

}

void EntryWindow::on_clientButton_clicked()
{
    this->close();
    loginWindow = new clientLogin();
}

void EntryWindow::on_serverButton_clicked()
{
    this->close();
    serverLogin = new ServerGUI();

}
