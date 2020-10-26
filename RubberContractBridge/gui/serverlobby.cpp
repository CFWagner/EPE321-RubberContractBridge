#include "serverlobby.h"
#include "ui_serverlobby.h"

ServerLobby::ServerLobby(QWidget *parent) :QWidget(parent), ui(new Ui::ServerLobby)
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
//    ui->playerList->addItem("MAT");
//    ui->playerList->addItem("PAT");
//    ui->playerList->takeItem(1);

    // Buttons setup such as the icons.
    ui->north_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->south_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->east_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->west_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    QPixmap createPixel(":/resources/guiResources/buttons/add_grey.png");

    //Label setup for the "START", "ADD" and "CLEAR" buttons.
    Hover *addPlayersB = new Hover(this->pageID,5,this);
    addPlayersB->setPixmap(createPixel);
    addPlayersB->setGeometry(90,320,150,64);
    //Connect the addPlayersB to Hover.
    connect(addPlayersB,&Hover::addPlayersLobby,this,&ServerLobby::addPlayersLobby);

    QPixmap clearPixel(":/resources/guiResources/buttons/clear_grey.png");
    Hover *clearLobby = new Hover(this->pageID,6,this);
    clearLobby->setPixmap(clearPixel);
    clearLobby->setGeometry(90,390,150,64);
    //Connect the clearLobby to Hover.
    connect(clearLobby,&Hover::clearPlayersLobby,this,&ServerLobby::clearPlayersLobby);

    QPixmap startPixel(":/resources/guiResources/buttons/start_grey.png");
    Hover *startGame = new Hover(this->pageID,7,this);
    startGame->setPixmap(startPixel);
    startGame->setGeometry(400,270,150,64);
    // Connect the startGameB and playersSelected form Hover to Server and ServerLobby.
    connect(startGame,&Hover::startGameB,this,&ServerLobby::startGameB);
    //connect(this,&ServerLobby::playersSelected,serverCreated,&Server::playersSelected);

}

QVector<QString> ServerLobby::getplayerNames()
{
    return playerNames;
}

void ServerLobby::addPlayersLobby()
{
    //Depending on the amount and which players are selected they are added to the lobby
    //once the "ADD" button is pressed.
    int amountAdd = 0;
    //Ensure the Lobby only contains 4 players and one can not add more than the
    //amount of open slots available.
    if (ui->playerList->selectedItems().length() > openSpots)
    {
        amountAdd = openSpots;
    }
    else
    {
        amountAdd = ui->playerList->selectedItems().length();
    }
    //Place the player in the next available slot.
    for (int i = 0; i < amountAdd; i++)
    {
        if (ui->north->text() == "")
        {
            ui->north->setText(ui->playerList->selectedItems()[i]->text());
            ui->north_b->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
            openSpots--;
        }
        else if(ui->south->text() == "")
        {
            ui->south->setText(ui->playerList->selectedItems()[i]->text());
            ui->south_b->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
            openSpots--;
        }
        else if(ui->east->text() == "")
        {
            ui->east->setText(ui->playerList->selectedItems()[i]->text());
            ui->east_b->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
            openSpots--;
        }
        else if(ui->west->text() == "")
        {
            ui->west->setText(ui->playerList->selectedItems()[i]->text());
            ui->west_b->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
            openSpots--;
        }
    }
}

void ServerLobby::clearPlayersLobby()
{
    //The lobby is just cleared to rearange players and BOTS. Clear ICON and labels.
    openSpots = 4;
    ui->north->setText("");
    ui->north_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->south->setText("");
    ui->south_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->east->setText("");
    ui->east_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->west->setText("");
    ui->west_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
}

void ServerLobby::startGameB()
{
    // Once the lobby is filled the game can start. All the player names are sent to the server
    // the game is then started with these players (BOTS or HUMANS)
    if(openSpots == 0)
    {
        playerNames[0] = ui->north->text();
        playerNames[1] = ui->south->text();
        playerNames[2] = ui->east->text();
        playerNames[3] = ui->west->text();
        emit playersSelected(playerNames);
    }
}
///////////////////////////////////////////////////////
/// Player is added to list of possible opponents.
///////////////////////////////////////////////////////
void ServerLobby::addPlayer(QString name)
{
    totalPlayers++;
    ui->playerList->addItem(name);
}

///////////////////////////////////////////////////////
/// Player is removed from list of possible opponents.
///////////////////////////////////////////////////////
void ServerLobby::removePlayer(QString name)
{
    for (int i =0;i < totalPlayers; i++)
    {
        if (ui->playerList->item(i)->text()== name)
        {
            ui->playerList->takeItem(i);
            break;
        }
    }
    totalPlayers --;
}

////////////////////////////////////////////////////////////////////////////////////////
/// All the on_xxx_b_clicked() slots receive a button clicked signal that cnahges the
/// lables as well as the the icons of the desired positions to a AI BOT.
////////////////////////////////////////////////////////////////////////////////////////
    void ServerLobby::on_north_b_clicked()
    {
        //North position is occupied by a bot.
        if(ui->north->text() == ""){
            ui->north->setText("BOT North");
            ui->north_b->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
            openSpots--;
        }
        else if (ui->north->text().contains("BOT"))
        {
            //North position is cleared and bot is removed.
            ui->north->setText("");
            ui->north_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
            openSpots++;
        }
    }

    void ServerLobby::on_east_b_clicked()
    {
        if(ui->east->text() == ""){
            ui->east->setText("BOT East");
            ui->east_b->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
            openSpots--;
        }
        else if (ui->east->text().contains("BOT"))
        {
            ui->east->setText("");
            ui->east_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
            openSpots++;
        }
    }

    void ServerLobby::on_west_b_clicked()
    {
        if(ui->west->text() == ""){
            ui->west->setText("BOT West");
            ui->west_b->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
            openSpots--;
        }
        else if (ui->west->text().contains("BOT"))
        {
            ui->west->setText("");
            ui->west_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
            openSpots++;
        }
    }

    void ServerLobby::on_south_b_clicked()
    {
        if(ui->south->text() == ""){
            ui->south->setText("BOT South");
            ui->south_b->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
            openSpots--;
        }
        else if (ui->south->text().contains("BOT"))
        {
            ui->south->setText("");
            ui->south_b->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
            openSpots++;
        }
    }
