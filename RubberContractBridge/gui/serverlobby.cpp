#include "serverlobby.h"
#include "ui_serverlobby.h"

ServerLobby::ServerLobby(Server *serverCreated, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerLobby)
{
    ui->setupUi(this);
    setupWindow();
    this->show();
}

ServerLobby::~ServerLobby()
{
    delete ui;
}

void ServerLobby::setupWindow()
{
    // QPixmap maps the pixels of the background fot the palatte to brush it onto the
    // current ui.
    QPixmap bkgnd(":/resources/guiResources/background/background3.png");
    bkgnd = bkgnd.scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //Fix the size of the window to a specified 415 by 520 ratio (16:12)
    this->setWindowTitle ("Rubber Contract Bridge");
}

void ServerLobby::staticGUIElements()
{

}
