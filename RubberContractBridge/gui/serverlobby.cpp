#include "serverlobby.h"
#include "ui_serverlobby.h"

QString playerList[4] = { "", "", "", ""};
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
        playerList[1] = "";
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
    if (ui->player1->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] != "BOT")
                {
                    playerList[i] = ui->player1->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon();
    }
}

void serverLobby::on_addPlayer2_stateChanged(int arg1)
{
    if (ui->player2->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] != "BOT")
                {
                    playerList[i] = ui->player2->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon();
    }
}

void serverLobby::on_addPlayer3_stateChanged(int arg1)
{
    if (ui->player3->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] != "BOT")
                {
                    playerList[i] = ui->player3->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon();
    }
}

void serverLobby::on_addPlayer4_stateChanged(int arg1)
{
    if (ui->player4->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] != "BOT")
                {
                    playerList[i] = ui->player4->text();
                    playeramount++;
                    break;
                }
            }
        }
        changeIcon();
    }
}

void serverLobby::on_addPlayer5_stateChanged(int arg1)
{
    if (ui->player5->text() != "")
    {
        if (playeramount <= 4)
        {
            for (int i =0; i <4;i++)
            {
                if(playerList[i] != "BOT")
                {
                    playerList[i] = ui->player4->text();
                    playeramount++;
                    break;
                }
            }
        }
    }
    changeIcon();
}
void serverLobby::lobbyStart()
{

}

void serverLobby::removePlayer(QString user)
{
    counter--;
    switch (counter)
    {
        case 1:
            ui->player1->setText("");
        break;

        case 2:
            ui->player2->setText("");
        break;

        case 3:
            ui->player3->setText("");
        break;

        case 4:
            ui->player4->setText("");
        break;

        case 5:
            ui->player5->setText("");
        break;
    }

}

void serverLobby::addPlayer(QString user)
{
    counter++;
    switch (counter)
    {
        case 1:
            ui->player1->setText(user);
        break;

        case 2:
            ui->player2->setText(user);
        break;

        case 3:
            ui->player3->setText(user);
        break;

        case 4:
            ui->player4->setText(user);
        break;

        case 5:
            ui->player5->setText(user);
        break;
    }

}
void serverLobby::changeIcon()
{
    if (playerList[0] != "" || playerList[0] != "BOT")
    {
        ui->north->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
    else if (playerList[1] != "" || playerList[1] != "BOT")
    {
        ui->east->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
    else if (playerList[2] != "" || playerList[2] != "BOT")
    {
        ui->south->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
    else if (playerList[3] != "" || playerList[3] != "BOT")
    {
        ui->west->setIcon(QIcon(":/resources/guiResources/background/userIcon.png"));
    }
}
