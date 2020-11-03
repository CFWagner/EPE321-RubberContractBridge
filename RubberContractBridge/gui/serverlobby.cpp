#include "serverlobby.h"
#include "ui_serverlobby.h"

ServerLobby::ServerLobby(QWidget *parent) :QWidget(parent), ui(new Ui::ServerLobby)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
}

ServerLobby::~ServerLobby()
{
    qDebug() << "Server close";
    emit closeServer();
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
    setWindowIcon(QIcon(":/resources/guiResources/cards/ace_hearts.png"));
}

void ServerLobby::staticGUIElements()
{
    //QListWidget setup allow multiple selected.
    ui->playerList->setSelectionMode(QAbstractItemView::ExtendedSelection);

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
    bool add = true;
    QString namesC [4] = {ui->north->text(),ui->south->text(),ui->east->text(),ui->west->text()};
    for(int i = 0;i < ui->playerList->selectedItems().length();++i)
    {
        if(namesC->contains(ui->playerList->selectedItems()[i]->text()))
        {
            add = false;
        }
    }
    if (add)
    {
        int amountAdd = 0;
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
}

void ServerLobby::clearPlayersLobby()
{
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
    int mayStart = true;
    if (ui->north->text() == ui->south->text()||ui->north->text() == ui->east->text()||ui->north->text() == ui->west->text())
    {
        mayStart = false;
    }
    if (ui->south->text() == ui->north->text()||ui->south->text() == ui->east->text()||ui->south->text() == ui->west->text())
    {
        mayStart = false;
    }
    if (ui->east->text() == ui->south->text()||ui->north->text() == ui->east->text()||ui->east->text() == ui->west->text())
    {
        mayStart = false;
    }
    if (ui->west->text() == ui->south->text()||ui->west->text() == ui->east->text()||ui->north->text() == ui->west->text())
    {
        mayStart = false;
    }
    if(mayStart)
    {
        if(openSpots == 0)
        {
            playerNames[0] = ui->north->text();
            playerNames[1] = ui->south->text();
            playerNames[2] = ui->east->text();
            playerNames[3] = ui->west->text();
            this->hide();
            emit rubberNumber(ui->rubberCount->text().toInt());
            emit playersSelected(playerNames);
            if(ui->rubberCount->text() == "" || ui->rubberCount->text().toInt()<1)
            {
                ui->rubberCount->text().clear();
                ui->rubberCount->text() = 1;
            }
        }
    }
}

void ServerLobby::addPlayer(QString name)
{
    totalPlayers++;
    ui->playerList->addItem(name);
}

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
void ServerLobby::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == 16777220 )
    {
        startGameB();
    }
}
