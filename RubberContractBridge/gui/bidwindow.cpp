#include "bidwindow.h"
#include "ui_bidwindow.h"

BidWindow::BidWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BidWindow)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
    setupBidTable();
    //this->showFullScreen();
}

BidWindow::~BidWindow()
{
    delete ui;
}

void BidWindow::setupWindow()
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

// This function is generic and is used in all windows.
void BidWindow::staticGUIElements()
{
    // The Background as well as the CallBid cards are created here.
    QPixmap arrowPix(":/resources/guiResources/bid/arrows.png");
    ui->label->setPixmap(arrowPix);
    QPixmap XP(":/resources/guiResources/bid/X.png");
    QPixmap XXP(":/resources/guiResources/bid/XX.png");
    QPixmap passP(":/resources/guiResources/bid/PASS.png");
    BidCardsSelected *X = new BidCardsSelected(DOUBLE_BID,this);
    X->setPixmap(XP);
    X->setGeometry(1200,500,101,61);
    connect(X,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    BidCardsSelected *XX = new BidCardsSelected(REDOUBLE_BID,this);
    XX->setPixmap(XXP);
    XX->setGeometry(1350,500,101,61);
    connect(XX,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    BidCardsSelected *passB = new BidCardsSelected(PASS,this);
    passB->setPixmap(passP);
    passB->setGeometry(1275,400,101,61);
    connect(passB,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));
    ui->you->setText("NORTH");
    ui->right->setText("WEST");
    ui->left->setText("EAST");
    ui->top->setText("SOUTH");
}

// Close the game using the button.
void BidWindow::on_button_exit_clicked()
{
    this->close();
}

// The clientNetwork sends the new game state to the user, to
// update the gui.
void BidWindow::getUpdateGameState(PlayerGameState player)
{
    this->player = player;
    ui->you->setText(name);
    //Check if it is your turn
    if(name == player.getPlayerName(player.getPlayerTurn()))
    {
        canMakeMove = true;
    }
    if(player.getContractBid() != nullptr)
    {
        updateBidDeck();
    }

}

// The bids are removed as the invalid bids fall away.
void BidWindow::updateBidDeck()
{
    int counter = 0;
    // Remove the first lines, then remove the specified suits.
    if (player.getContractBid()->getTricksAbove() == 1)
    {
        for(int i = 0; i < player.getContractBid()->getTrumpSuit();i++)
        {
            bidCards[i*7]->hide();
        }
    }
    else
    {
        for(int i = 0; i < player.getContractBid()->getTricksAbove()-1;i++)
        {
            bidCards[i]->hide();
            bidCards[i + 7]->hide();
            bidCards[i + 14]->hide();
            bidCards[i + 21]->hide();
            bidCards[i + 28]->hide();
            counter++;
        }
        for(int i = 0; i < player.getContractBid()->getTrumpSuit();i++)
        {
            bidCards[counter+i*7]->hide();
        }
    }
    bidCards[(player.getContractBid()->getTricksAbove()-1)+player.getContractBid()->getTrumpSuit()*7]->setGeometry(10,10,61,101);
}

// The bid has been selected and will then be sent to the
// clientNetwork.
void BidWindow::bidPressed(BidCardsSelected *bidReceived)
{
    if(canMakeMove && bidReceived->pos() != QPoint(10,10))
    {
        Bid bidMade(player.getPlayerTurn(),bidReceived->getSuit(),bidReceived->getValue());
        emit txBidSelected(bidMade);
    }
}

// The cards are created and displayed here.
// The bidCards index is used to create the assets using code and not hard coded.
void BidWindow::setupBidTable()
{
    QString imageName = "background-image: url(:/resources/guiResources/bid/";
    QString cardName;
    //Create the bid labels that every person can choose from.
    for (int i = 0; i < 7;i++)
    {

        bidCard = new BidCardsSelected(CLUBS,i+1,this);
        bidCards[i] = bidCard;
        cardName = imageName + "clubs_"+QString::number(i+1)+".png)";
        bidCards[i]->setStyleSheet(cardName);
        bidCards[i]->setGeometry(1020,300+30*i,61,101);
        connect(bidCard,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);

    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(DIAMONDS,i+1,this);
        bidCards[i+7] = bidCard;
        cardName = imageName + "diamond_"+QString::number(i+1)+".png)";
        bidCards[i+7]->setStyleSheet(cardName);
        bidCards[i+7]->setGeometry(920,300+30*i,61,101);
        connect(bidCard,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(HEARTS,i+1,this);
        bidCards[i+14] = bidCard;
        cardName = imageName + "heart_"+QString::number(i+1)+".png)";
        bidCards[i+14]->setStyleSheet(cardName);
        bidCards[i+14]->setGeometry(820,300+30*i,61,101);
        connect(bidCard,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(SPADES,i+1,this);
        bidCards[i+21] = bidCard;
        cardName = imageName + "spade_"+QString::number(i+1)+".png)";
        bidCards[i+21]->setStyleSheet(cardName);
        bidCards[i+21]->setGeometry(720,300+30*i,61,101);
        connect(bidCard,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(NONE,i+1,this);
        bidCards[i+28] = bidCard;
        cardName = imageName + "NT_"+QString::number(i+1)+".png)";
        bidCards[i+28]->setStyleSheet(cardName);
        bidCards[i+28]->setGeometry(620,300+30*i,61,101);
        connect(bidCard,&BidCardsSelected::sendBidPressed,this,&BidWindow::bidPressed);
    }
}

void BidWindow::setName(QString name)
{
    this->name = name;
}
