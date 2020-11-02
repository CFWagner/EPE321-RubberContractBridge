#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(ClientNetwork *clientNetwork, QWidget *parent) : QWidget(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->clientNetwork = clientNetwork;
    connect(clientNetwork,&ClientNetwork::updateGameState, this,&GameWindow::updateGameState);
    connect(clientNetwork,&ClientNetwork::generalError, this,&GameWindow::generalError);
    connect(clientNetwork,&ClientNetwork::gameTerminated, this,&GameWindow::gameTerminated);
    connect(clientNetwork,&ClientNetwork::notifyBidTurn, this,&GameWindow::playerTurnBid);
    connect(clientNetwork,&ClientNetwork::notifyBidRejected, this,&GameWindow::bidRejected);
    connect(this,&GameWindow::bidAction, clientNetwork,&ClientNetwork::txBidSelected);
    setupWindow();
    staticGUIElements();
    this->showFullScreen();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setupWindow()
{
    QPixmap bkgnd(":/resources/guiResources/background/background1.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(1920,1080);
    this->setWindowTitle ("Rubber Contract Bridge");
}

void GameWindow::staticGUIElements()
{
    QPixmap arrowPix(":/resources/guiResources/background/bidBoard.png");
    QLabel *frame = new QLabel(this);
    frame->setPixmap(arrowPix);
    frame->setGeometry(356,186,1208,708);
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));

    QPixmap XP(":/resources/guiResources/bid/X.png");
    QPixmap XXP(":/resources/guiResources/bid/XX.png");
    QPixmap passP(":/resources/guiResources/bid/PASS.png");
    BidSelect *X = new BidSelect(DOUBLE_BID,this);
    X->setPixmap(XP);
    X->setGeometry(860,600,101,61);
    connect(X,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
    BidSelect *XX = new BidSelect(REDOUBLE_BID,this);
    XX->setPixmap(XXP);
    XX->setGeometry(1000,600,101,61);
    connect(XX,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
    BidSelect *passB = new BidSelect(PASS,this);
    passB->setPixmap(passP);
    passB->setGeometry(760,600,101,61);
    connect(passB,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
}

void GameWindow::updateGameState(PlayerGameState gameState)
{
    this->gameState = gameState;
    qDebug() << "Receive the gameState: "<< gameState.getEvent();
    qDebug() <<"Player name: " <<name;
    qDebug() <<"Player turn: " <<gameState.getPlayerName(gameState.getPlayerTurn());
    this->gameState = gameState;
    switch(gameState.getEvent())
    {
    case (BID_START):
    {
        createBidTable();
        break;
    }
    case (PLAYER_BID):
    {
        updateBidTable();
        break;
    }
    default:
        break;
    }
}

void GameWindow::updateBidTable()
{
    int counter = 0;
    if (gameState.getCurrentBid()->getTricksAbove() == 1)
    {
        for(int i = 0; i < gameState.getCurrentBid()->getTrumpSuit();i++)
        {
            bidTable[i*7]->hide();
        }
    }
    else
    {
        for(int i = 0; i < gameState.getCurrentBid()->getTricksAbove()-1;i++)
        {
            bidTable[i]->hide();
            bidTable[i + 7]->hide();
            bidTable[i + 14]->hide();
            bidTable[i + 21]->hide();
            bidTable[i + 28]->hide();
            counter++;
        }
        for(int i = 0; i < gameState.getCurrentBid()->getTrumpSuit();i++)
        {
            bidTable[counter+i*7]->hide();
        }
    }
    bidTable[(gameState.getCurrentBid()->getTricksAbove()-1)+gameState.getCurrentBid()->getTrumpSuit()*7]->setGeometry(10,10,61,31);
}

void GameWindow::receiveBid(BidSelect *bidSelected)
{
    this->bidSelected = bidSelected;
    if (gameState.getPlayerName(gameState.getPlayerTurn())==name)
    {
        if(bidSelected->getBidCall() == BID)
        {
            playerMayBid = false;
            qDebug() << "Bid made: " <<  bidSelected->getValue();
            Bid bidMade(gameState.getPlayerTurn(),bidSelected->getSuit(),bidSelected->getValue());
            emit bidAction(bidMade);
        }
        else
        {
           playerMayBid = false;
           qDebug() << "PASS: " <<  bidSelected->getBidCall();
//           Bid bidMade(gameState.getPlayerTurn(),bidSelected->getBidCall());
//           emit bidAction(bidMade);
        }
    }
}

void GameWindow::createBidTable()
{
    QString imageName = "background-image: url(:/resources/guiResources/bid/";
    QString cardName;
    //Create the bid labels that every person can choose from.
    for (int i = 0; i < 7;i++)
    {

        bids= new BidSelect(CLUBS,i+1,this);
        bidTable[i] = bids;
        cardName = imageName + "clubs_"+QString::number(i+1)+".png)";
        bidTable[i]->setStyleSheet(cardName);
        bidTable[i]->setGeometry(1100,300+40*i,61,31);
        connect(bids,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
        bidTable[i]->show();

    }
    for (int i = 0; i < 7;i++)
    {
        bids= new BidSelect(DIAMONDS,i+1,this);
        bidTable[i+7] = bids;
        cardName = imageName + "diamonds_"+QString::number(i+1)+".png)";
        bidTable[i+7]->setStyleSheet(cardName);
        bidTable[i+7]->setGeometry(1015,300+40*i,61,31);
        connect(bids,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
        bidTable[i+7]->show();
    }
    for (int i = 0; i < 7;i++)
    {
        bids= new BidSelect(HEARTS,i+1,this);
        bidTable[i+14] = bids;
        cardName = imageName + "hearts_"+QString::number(i+1)+".png)";
        bidTable[i+14]->setStyleSheet(cardName);
        bidTable[i+14]->setGeometry(930,300+40*i,61,31);
        connect(bids,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
        bidTable[i+14]->show();
    }
    for (int i = 0; i < 7;i++)
    {
        bids= new BidSelect(SPADES,i+1,this);
        bidTable[i+21] = bids;
        cardName = imageName + "spades_"+QString::number(i+1)+".png)";
        bidTable[i+21]->setStyleSheet(cardName);
        bidTable[i+21]->setGeometry(845,300+40*i,61,31);
        connect(bids,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
        bidTable[i+21]->show();
    }
    for (int i = 0; i < 7;i++)
    {
        bids= new BidSelect(NONE,i+1,this);
        bidTable[i+28] = bids;
        cardName = imageName + "NT_"+QString::number(i+1)+".png)";
        bidTable[i+28]->setStyleSheet(cardName);
        bidTable[i+28]->setGeometry(760,300+40*i,61,31);
        connect(bids,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
        bidTable[i+28]->show();
    }
}

void GameWindow::setName(QString username)
{
    this->name = username;
}

void GameWindow::gameTerminated(QString reason)
{
    QMessageBox::warning(this,"Error message",reason);
    this->close();
}

void GameWindow::generalError(QString errorMsg)
{
    QMessageBox::warning(this,"Error message",errorMsg);
}

void GameWindow::playerTurnBid()
{
    qDebug() << "PLAYER MUST PLAY: "<< name;
    playerMayBid = true;
}

void GameWindow::bidRejected(QString reason)
{
    qDebug() <<reason;
}

void GameWindow::setGameState(PlayerGameState gameState)
{
    this->gameState = gameState;
    if (name == gameState.getPlayerName(NORTH))
    {
        ui->you->setText(gameState.getPlayerName(NORTH));
        ui->left->setText(gameState.getPlayerName(EAST));
        ui->top->setText(gameState.getPlayerName(SOUTH));
        ui->right->setText(gameState.getPlayerName(WEST));
    }
    else if (name == gameState.getPlayerName(EAST))
    {
        ui->you->setText(gameState.getPlayerName(EAST));
        ui->left->setText(gameState.getPlayerName(NORTH));
        ui->top->setText(gameState.getPlayerName(WEST));
        ui->right->setText(gameState.getPlayerName(SOUTH));
    }
    else if (name == gameState.getPlayerName(WEST))
    {
        ui->you->setText(gameState.getPlayerName(WEST));
        ui->left->setText(gameState.getPlayerName(SOUTH));
        ui->top->setText(gameState.getPlayerName(EAST));
        ui->right->setText(gameState.getPlayerName(NORTH));
    }
    else if (name == gameState.getPlayerName(SOUTH))
    {
        ui->you->setText(gameState.getPlayerName(SOUTH));
        ui->left->setText(gameState.getPlayerName(WEST));
        ui->top->setText(gameState.getPlayerName(NORTH));
        ui->right->setText(gameState.getPlayerName(EAST));
    }
    ui->you->show();
    ui->left->show();
    ui->top->show();
    ui->right->show();
    ui->you->raise();
    ui->left->raise();
    ui->top->raise();
    ui->right->raise();
}

void GameWindow::on_button_exit_clicked()
{
    this->close();
}
