#include "bridgewindow.h"
#include "ui_bridgewindow.h"

bridgeWindow::bridgeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bridgeWindow)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
    for (int i = 0; i < 13;++i)
    {
        cardsInHand[i] = nullptr;
    }
}

bridgeWindow::~bridgeWindow()
{
    for (int i = 0; i < 13;++i)
    {
        if(cardsInHand[i])
        {
            delete cardsInHand[i];
        }
    }
    delete ui;
}

void bridgeWindow::setupWindow()
{
    // QPixmap maps the pixels of the background fot the palatte to brush it onto the
    // current ui.
    QPixmap bkgnd(":/resources/guiResources/background/background1.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //Fix the size of the window to a specified 415 by 520 ratio (16:12)
    this->setFixedSize(1920,1080);
    this->setWindowTitle ("Rubber Contract Bridge Bid");
}

void bridgeWindow::staticGUIElements()
{
    QPixmap arrowPix(":/resources/guiResources/bid/arrows.png");
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));
    ui->label->setPixmap(arrowPix);
    ui->you->setText("NORTH");
    ui->right->setText("WEST");
    ui->left->setText("EAST");
    ui->top->setText("SOUTH");
}

// The hand is created by placing all the needed labels.
// Images are created from the hand received.
void bridgeWindow::setupHand()
{
    QString imageName = "background-image: url(:/resources/guiResources/cards/";
    QString cardName;
    for(int i = 0; i < 13;i++)
    {
        if(player.getPlayerHand().getCard(i).getRank() == 1)
        {
            cardName = "two_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 2)
        {
            cardName = "three_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 3)
        {
            cardName = "four_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 4)
        {
            cardName = "five_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 5)
        {
            cardName = "six_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 6)
        {
            cardName = "seven_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 7)
        {
            cardName = "eight_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 8)
        {
            cardName = "nine_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 9)
        {
            cardName = "ten_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 10)
        {
            cardName = "jack_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 11)
        {
            cardName = "queen_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 12)
        {
            cardName = "king_";
        }
        else if (player.getPlayerHand().getCard(i).getRank() == 13)
        {
            cardName = "ace_";
        }
        if(player.getPlayerHand().getCard(i).getSuit() == 0)
        {
            cardName+= "clubs.png)";
        }
        else if(player.getPlayerHand().getCard(i).getSuit() == 1)
        {
            cardName+= "diamonds.png)";
        }
        else if(player.getPlayerHand().getCard(i).getSuit() == 2)
        {
            cardName+= "hearts.png)";
        }
        else if(player.getPlayerHand().getCard(i).getSuit() == 3)
        {
            cardName+= "spades.png)";
        }
        if (cardsInHand[i])
            delete cardsInHand[i];
        cardMine = new PlayCardSelected(this);
        cardsInHand[i] = cardMine;
        cardsInHand[i] ->setStyleSheet(imageName+cardName);
        cardsInHand[i] ->setGeometry(820+ i*30,940,101,141);
        connect(cardsInHand[i],&PlayCardSelected::sendCardPlayed,this,&bridgeWindow::getCardChosen);
        cardsInHand[i]->show();
    }


}
//Once the game state is received all players must first get their
//hand.
void bridgeWindow::getUpdateGameState(PlayerGameState player)
{
    this->player = player;
    this->repaint();
    if(player.getEvent()==PLAY_START)
    {
        setupHand();
    }
}

// Move the chosen car toi the trick. Here I would send the card played to the
// client network.
void bridgeWindow::getCardChosen(PlayCardSelected *cardPlayed)
{
    if (count == 0)
    {
        cardPlayed->setGeometry(900,500,101,141);
        count++;
    }
    else if (count == 1)
    {
        cardPlayed->setGeometry(800,450,101,141);
        count++;
    }
    else if (count == 2)
    {
        cardPlayed->setGeometry(900,400,101,141);
        count++;
    }
    else if (count == 3)
    {
        cardPlayed->setGeometry(1000,450,101,141);
        count++;
    }
}

void bridgeWindow::on_button_exit_clicked()
{
    this->close();
}
