#include "serverlobby.h"
#include "ui_serverlobby.h"

QString playerList[4] = { "", "", "", ""};
int filled[5] = {0,0,0,0,0};
int counter = 0;
int playeramount = 0;
serverLobby::serverLobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverLobby)
{
    ui->setupUi(this);
    this->show();
    windowSetup();
}

serverLobby::~serverLobby()
{
    delete ui;
    lobbyStart();
    windowSetup();

}

void serverLobby::windowSetup()
{
    //Set up the background pixelmap
    QPixmap background(":/resources/guiResources/background/background3.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    //Draw the background into the desired size.
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    //Specify size.
    this->setFixedSize(640,373);
    serverLobby::setWindowTitle ("Rubber Contract Bridge Lobby");
    ui->north->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->south->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->east->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    ui->west->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
}

void serverLobby::on_south_clicked()

{
    if (playerList[2] == "BOT")
    {
        playerList[2] = "";
        ui->south->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
        playeramount--;
    }
    else if (playerList[2] == "")
    {
        playerList[2] = "BOT";
        ui->south->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
        playeramount++;
    }
}

void serverLobby::on_west_clicked()
{
    if (playerList[3] == "BOT")
    {
        playerList[3] = "";
        ui->west->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
        playeramount--;
    }
    else if (playerList[3] == "")
    {
        playerList[3] = "BOT";
        ui->west->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
        playeramount++;
    }

}

void serverLobby::on_east_clicked()
{
    if (playerList[1] == "BOT")
    {
        playerList[1] = "";
        ui->east->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
        playeramount--;
    }
    else if (playerList[1] == "")
    {
        playerList[1] = "BOT";
        ui->east->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
        playeramount++;
    }
}

void serverLobby::on_north_clicked()
{
    if (playerList[0] == "BOT")
    {
        playerList[0] = "";
        ui->north->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
        playeramount--;
    }
    else if (playerList[0] == "")
    {
        playerList[0] = "BOT";
        ui->north->setIcon(QIcon(":/resources/guiResources/background/robot.png"));
        playeramount++;
    }
}

void serverLobby::on_addPlayer1_stateChanged(int arg1)
{
    int pos = -1;
    if (arg1 == 2){
        if (ui->player1->text() != "")
        {
            if (playeramount <= 4)
            {
                for (int i =0; i <4;i++)
                {
                    if(playerList[i] == "")
                    {
                        playerList[i] = ui->player1->text();
                        playeramount++;
                        break;
                    }
                }
            }
            changeIcon(ui->player1->text());
        }
    }
    else
    {
        for (int i =0; i <4;i++)
        {
            if(playerList[i] == ui->player1->text())
            {
                pos = i;
                playerList[i] = "";
                playeramount--;
                break;
            }
        }
        removeSpot(pos);

    }
}

void serverLobby::on_addPlayer2_stateChanged(int arg1)
{
    int pos = -1;
    if (arg1 == 2){
    if (ui->player2->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i]== "")
                {
                    playerList[i] = ui->player2->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon(ui->player2->text());
    }
    }
    else
    {
        for (int i =0; i <4;i++)
        {
            if(playerList[i] == ui->player2->text())
            {
                pos = i;
                playerList[i] = "";
                playeramount--;
                break;
            }
        }
        removeSpot(pos);

    }
}

void serverLobby::on_addPlayer3_stateChanged(int arg1)
{
    int pos = -1;
    if (arg1 == 2){
    if (ui->player3->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] == "")
                {
                    playerList[i] = ui->player3->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon(ui->player3->text());
    }
    }
    else
    {
        for (int i =0; i <4;i++)
        {
            if(playerList[i] == ui->player3->text())
            {
                pos = i;
                playerList[i] = "";
                playeramount--;
                break;
            }
        }
        removeSpot(pos);

    }
}

void serverLobby::on_addPlayer4_stateChanged(int arg1)
{
    int pos = -1;
    if (arg1 == 2){
    if (ui->player4->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] == "")
                {
                    playerList[i] = ui->player4->text();
                    playeramount++;
                    break;
                }
            }
        }
    }
        changeIcon(ui->player4->text());
    }
    else
    {
        for (int i =0; i <4;i++)
        {
            if(playerList[i] == ui->player4->text())
            {
                pos = i;
                playerList[i] = "";
                playeramount--;
                break;
            }
        }
        removeSpot(pos);

    }
}

void serverLobby::on_addPlayer5_stateChanged(int arg1)
{
    int pos = -1;
    if (arg1 == 2){
    if (ui->player5->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] == "")
                {
                    playerList[i] = ui->player4->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon(ui->player5->text());
    }
    }
    else
    {
        for (int i =0; i <4;i++)
        {
            if(playerList[i] == ui->player5->text())
            {
                pos = i;
                playerList[i] = "";
                playeramount--;
                break;
            }
        }
        removeSpot(pos);

    }
}
void serverLobby::lobbyStart()
{

}

void serverLobby::removePlayer(QString user)
{
    //A player is removed and the label is cleaned to allow for another person to join.
    int pos = -1;
    if (ui->player1->text() == user)
    {
        ui->player1->setText("");
        filled[0] = 0;
    }
    else if (ui->player2->text() == user)
    {
        ui->player2->setText("");
        filled[1] = 0;
    }
    else if (ui->player3->text() == user)
    {
        ui->player3->setText("");
        filled[2] = 0;
    }
    else if (ui->player4->text() == user)
    {
        ui->player4->setText("");
        filled[3] = 0;
    }
    else if (ui->player5->text() == user)
    {
        ui->player5->setText("");
        filled[4] = 0;
    }

}

void serverLobby::addPlayer(QString user)
{
    // the slot adds a player that has succesfully joined the server.
    int pos = -1;
    for (int i =0; i <=4;i++)
    {
        if (filled[i] == 0)
        {
            filled[i]=1;
            pos = i;
            break;
        }
    }
    if (pos == 0)
    {
        ui->player1->setText(user);
    }
    else if (pos == 1)
    {
        ui->player2->setText(user);
    }
    else if (pos == 2)
    {
        ui->player2->setText(user);
    }
    else if (pos == 3)
    {
        ui->player3->setText(user);
    }
    else if (pos == 4)
    {
        ui->player4->setText(user);
    }

}
void serverLobby::changeIcon(QString name)
{
    //If a user is selected they are placeed in the next available slot.
    if (playerList[0] == name)
    {
        ui->north->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
    else if (playerList[1] == name)
    {
        ui->east->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
    else if (playerList[2] == name)
    {
        ui->south->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
    else if (playerList[3] == name)
    {
        ui->west->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
}

void serverLobby::removeSpot(int pos)
{
    //The icon is removed from the slots if the person is deselected.
    if(pos == 0)
    {
        ui->north->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    }
    else if (pos == 1)
    {
        ui->east->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    }
    else if (pos == 2)
    {
        ui->south->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    }
    else if (pos == 3)
    {
        ui->west->setIcon(QIcon(":/resources/guiResources/background/playerBackground.png"));
    }
}
