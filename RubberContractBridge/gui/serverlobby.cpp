#include "serverlobby.h"
#include "ui_serverlobby.h"

ServerLobby::ServerLobby(Server *serverCreated, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerLobby)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
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
    //QListWidget setup allow multiple selected.
    ui->playerList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    playersLabels[0] = ui->north;
    playersLabels[1] = ui->south;
    playersLabels[2] = ui->east;
    playersLabels[3] = ui->west;
    QPixmap createPixel(":/resources/guiResources/buttons/add_grey.png");
    Hover *addPlayersB = new Hover(this->pageID,5,this);
    addPlayersB->setPixmap(createPixel);
    addPlayersB->setGeometry(90,320,150,64);
    connect(addPlayersB,&Hover::addPlayersLobby,this,&ServerLobby::addPlayersLobby);

//    Hover *startGame = new Hover(this->pageID,6,this);
//    startGame->setPixmap(createPixel);
//    startGame->setGeometry(90,320,150,64);

}

void ServerLobby::addPlayersLobby()
{
    qDebug() << playersLabels[0]->text();
}

void ServerLobby::on_east_button_clicked()
{

}

void ServerLobby::on_north_button_clicked()
{

}

void ServerLobby::on_south_button_clicked()
{

}

void ServerLobby::on_west_button_clicked()
{

}
