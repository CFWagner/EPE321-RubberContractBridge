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
    connect(clientNetwork,&ClientNetwork::notifyMoveTurn, this,&GameWindow::playerTurnMove);
    connect(clientNetwork,&ClientNetwork::notifyBidRejected, this,&GameWindow::bidRejected);
    connect(clientNetwork,&ClientNetwork::notifyMoveRejected, this,&GameWindow::moveRejected);
    connect(this,&GameWindow::bidAction, clientNetwork,&ClientNetwork::txBidSelected);
    connect(this,&GameWindow::cardAction, clientNetwork,&ClientNetwork::txMoveSelected);
    setupWindow();
    staticGUIElements();
    this->showFullScreen();
}

GameWindow::~GameWindow()
{
    delete ui;
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
        indicatePlayerTurn();
        gameBoard->hide();
        bidBoard->show();
        X->show();
        passB->show();
        XX->show();
        createBidTable();
        createHandTable();
        cardsClickable = false;
        break;
    }
    case (BID_RESTART):
    {
        indicatePlayerTurn();
        for (int i = 0; i < 13;i++)
        {
            if(cardsInHand[i] != nullptr)
            {
                delete cardsInHand[i];
            }
        }
        createHandTable();
        break;
    }
    case (PLAYER_BID):
    {
        indicatePlayerTurn();
        updateBidTable();
        break;
    }
    case (BID_END):
    {
        for(int i = 0; i < 35;++i)
        {
            if(bidTable[i] != nullptr)
            {
                bidTable[i]->hide();
            }
        }
        X->hide();
        passB->hide();
        XX->hide();
        break;
    }
    case (PLAY_START):
    {
        indicatePlayerTurn();
        bidBoard->hide();
        gameBoard->show();
        cardsClickable = true;
        break;
    }
    case (TRICK_START):
    {
        indicatePlayerTurn();
        trickPos = 0;
        break;
    }
    case (PLAYER_MOVED):
    {
        indicatePlayerTurn();
        addCardToTrick();
        trickPos += 1;
        break;
    }
    case(TRICK_END):
    {
        qDebug() << "END of trick";
        trickPos = 0;
        break;
    }
    default:
        break;
    }
}

void GameWindow::receiveCard(CardSelected *card)
{
    if (cardsClickable && playerMayPlay)
    {
        playerMayPlay = false;
        qDebug() << "Card selected "<< card->getSuit() << card->getRank();
        Card cardPlayed(card->getSuit(),card->getRank());
        emit cardAction(cardPlayed);
    }
}

void GameWindow::createBidTable()
{
    if(bidTableCreated == false)
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
    else
    {
        for (int i = 0; i < 7;i++)
        {
            bidTable[i]->setGeometry(1100,300+40*i,61,31);
            bidTable[i+7]->setGeometry(1015,300+40*i,61,31);
            bidTable[i+14]->setGeometry(930,300+40*i,61,31);
            bidTable[i+21]->setGeometry(845,300+40*i,61,31);
            bidTable[i+28]->setGeometry(760,300+40*i,61,31);
            bidTable[i]->show();
            bidTable[i+24]->show();
            bidTable[i+21]->show();
            bidTable[i+28]->show();
            bidTable[i+7]->show();
        }
    }
    bidTableCreated = true;
}

void GameWindow::addCardToTrick()
{
    qDebug() <<"Move card";
//    QString styleTrick ="";
//    int trickPositions = gameState.playerPositions.key(name) - gameState.getPlayerTurn()-1;
//    if (trickPositions == 0)
//    {
//        trickPositions = 0;
//        trickTabel[trickPositions] = new QLabel(this);
//        styleTrick = getStyle(trickPositions);
//        qDebug() <<"a";
//        trickTabel[trickPositions] ->setStyleSheet(styleTrick);
//        qDebug() <<"x";
//        trickTabel[trickPositions]->setGeometry(1000,890,61,31);
//        qDebug() <<"z";
//        trickTabel[trickPositions]->show();
//    }
//    else if (trickPositions == -1 || trickPositions == 3)
//    {
//        trickPositions = 1;
//        trickTabel[trickPositions] = new QLabel(this);
//        styleTrick = getStyle(trickPositions);
//        trickTabel[trickPositions] ->setStyleSheet(styleTrick);
//        trickTabel[trickPositions]->setGeometry(310,560,61,31);
//        trickTabel[trickPositions]->show();
//    }
//    else if (trickPositions == -2 || trickPositions == 2)
//    {
//        trickPositions = 2;
//        trickTabel[trickPositions] = new QLabel(this);
//        styleTrick = getStyle(trickPositions);
//        trickTabel[trickPositions] ->setStyleSheet(styleTrick);
//        trickTabel[trickPositions]->setGeometry(1000,146,61,31);
//        trickTabel[trickPositions]->show();
//    }
//    else if (trickPositions == -3 || trickPositions == 1)
//    {
//        trickPositions = 3;
//        trickTabel[trickPositions] = new QLabel(this);
//        styleTrick = getStyle(trickPositions);
//        trickTabel[trickPositions] ->setStyleSheet(styleTrick);
//        trickTabel[trickPositions]->setGeometry(1550,560,61,31);
//        trickTabel[trickPositions]->show();
//    }
//    qDebug() <<"aaaa";
}

//Finished
//////////////////////////////////////////////////////////
void GameWindow::updateBidTable()
{
    if (gameState.getCurrentBid() != nullptr)
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

        qDebug() << "My pos: "<<gameState.playerPositions.key(name);
        qDebug() << "Bid pos: "<<gameState.getCurrentBid()->bidder;
        int bidmaker = gameState.playerPositions.key(name) - gameState.getCurrentBid()->bidder;
        if (bidmaker == 0)
        {
            bidTable[(gameState.getCurrentBid()->getTricksAbove()-1)+gameState.getCurrentBid()->getTrumpSuit()*7]->setGeometry(1000,890,61,31);
        }
        else if (bidmaker == -1 || bidmaker == 3)
        {
            bidTable[(gameState.getCurrentBid()->getTricksAbove()-1)+gameState.getCurrentBid()->getTrumpSuit()*7]->setGeometry(310,560,61,31);
        }
        else if (bidmaker == -2 || bidmaker == 2)
        {
            bidTable[(gameState.getCurrentBid()->getTricksAbove()-1)+gameState.getCurrentBid()->getTrumpSuit()*7]->setGeometry(1000,146,61,31);
        }
        else if (bidmaker == -3 || bidmaker == 1)
        {
            bidTable[(gameState.getCurrentBid()->getTricksAbove()-1)+gameState.getCurrentBid()->getTrumpSuit()*7]->setGeometry(1550,560,61,31);
        }
    }
}

QString GameWindow::getStyle(int)
{
//    qDebug() <<"Style";
//    QString imageName = "background-image: url(:/resources/guiResources/cards/";
//    if(gameState.getTricks().end()->getCard(0).getRank() == 1)
//    {
//        imageName += "two_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 2)
//    {
//        imageName += "three_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 3)
//    {
//        imageName += "four_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 4)
//    {
//        imageName += "five_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 5)
//    {
//        imageName += "six_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 6)
//    {
//        imageName += "seven_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 7)
//    {
//        imageName += "eight_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 8)
//    {
//        imageName += "nine_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 9)
//    {
//        imageName += "ten_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 10)
//    {
//        imageName += "jack_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 11)
//    {
//        imageName += "queen_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 12)
//    {
//        imageName += "king_";
//    }
//    else if (gameState.getTricks().end()->getCard(0).getRank() == 13)
//    {
//        imageName += "ace_";
//    }
//    if(gameState.getTricks().end()->getCard(0).getSuit() == 0)
//    {
//        imageName += "clubs.png)";
//    }
//    else if(gameState.getTricks().end()->getCard(0).getSuit() == 1)
//    {
//        imageName += "diamonds.png)";
//    }
//    else if(gameState.getTricks().end()->getCard(0).getSuit() == 2)
//    {
//        imageName += "hearts.png)";
//    }
//    else if(gameState.getTricks().end()->getCard(0).getSuit() == 3)
//    {
//        imageName += "spades.png)";
//    }
//    qDebug() <<"Get style";
//    qDebug() <<imageName;
    //    return imageName;
}

void GameWindow::createHandTable()
{
    CardSet playerHand = gameState.getPlayerHand();
    playerHand.orderHand();
    QString imageName = "background-image: url(:/resources/guiResources/cards/";
    QString cardName;
    for(int i = 0; i < 13;i++)
    {
        if(playerHand.getCard(i).getRank() == 1)
        {
            cardName = "two_";
        }
        else if (playerHand.getCard(i).getRank() == 2)
        {
            cardName = "three_";
        }
        else if (playerHand.getCard(i).getRank() == 3)
        {
            cardName = "four_";
        }
        else if (playerHand.getCard(i).getRank() == 4)
        {
            cardName = "five_";
        }
        else if (playerHand.getCard(i).getRank() == 5)
        {
            cardName = "six_";
        }
        else if (playerHand.getCard(i).getRank() == 6)
        {
            cardName = "seven_";
        }
        else if (playerHand.getCard(i).getRank() == 7)
        {
            cardName = "eight_";
        }
        else if (playerHand.getCard(i).getRank() == 8)
        {
            cardName = "nine_";
        }
        else if (playerHand.getCard(i).getRank() == 9)
        {
            cardName = "ten_";
        }
        else if (playerHand.getCard(i).getRank() == 10)
        {
            cardName = "jack_";
        }
        else if (playerHand.getCard(i).getRank() == 11)
        {
            cardName = "queen_";
        }
        else if (playerHand.getCard(i).getRank() == 12)
        {
            cardName = "king_";
        }
        else if (playerHand.getCard(i).getRank() == 13)
        {
            cardName = "ace_";
        }
        if(playerHand.getCard(i).getSuit() == 0)
        {
            cardName+= "clubs.png)";
        }
        else if(playerHand.getCard(i).getSuit() == 1)
        {
            cardName+= "diamonds.png)";
        }
        else if(playerHand.getCard(i).getSuit() == 2)
        {
            cardName+= "hearts.png)";
        }
        else if(playerHand.getCard(i).getSuit() == 3)
        {
            cardName+= "spades.png)";
        }
        cardMine = new CardSelected(playerHand.getCard(i).getSuit(),playerHand.getCard(i).getRank(),this);
        cardsInHand[i] = cardMine;
        cardsInHand[i] ->setStyleSheet(imageName+cardName);
        cardsInHand[i] ->setGeometry(720+ i*30,940,101,141);
        connect(cardsInHand[i],&CardSelected::sendCardPlayed,this,&GameWindow::receiveCard);
        cardsInHand[i]->show();
    }
}

void GameWindow::indicatePlayerTurn()
{
    int turnPosition = gameState.playerPositions.key(name) - gameState.getPlayerTurn();
    if (turnPosition == 0)
    {
        turnIndicator->setGeometry(800,800,51,51);
    }
    else if (turnPosition == -1 || turnPosition == 3)
    {
        turnIndicator->setGeometry(500,520,51,51);
    }
    else if (turnPosition == -2 || turnPosition == 2)
    {
        turnIndicator->setGeometry(800,220,51,51);
    }
    else if (turnPosition == -3 || turnPosition == 1)
    {
        turnIndicator->setGeometry(1400,520,51,51);
    }
    turnIndicator->show();
}

void GameWindow::receiveBid(BidSelect *bidSelected)
{
    this->bidSelected = bidSelected;
    if (playerMayBid)
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
            qDebug() << "PASS: " <<  bidSelected->getBidCall() << "FOR: "<<gameState.getPlayerTurn();
            Bid bidMade(gameState.getPlayerTurn(),bidSelected->getBidCall());
            emit bidAction(bidMade);
        }
    }
}

//SMALL FUNCTIONS//
void GameWindow::playerTurnBid()
{
    qDebug() << "YOU MAY BID";
    playerMayBid = true;
}

void GameWindow::playerTurnMove()
{
    qDebug() << "YOU MAY MAKE CARD CHOICE";
    playerMayPlay = true;
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
        ui->left->setText(gameState.getPlayerName(SOUTH));
        ui->top->setText(gameState.getPlayerName(WEST));
        ui->right->setText(gameState.getPlayerName(NORTH));
    }
    else if (name == gameState.getPlayerName(WEST))
    {
        ui->you->setText(gameState.getPlayerName(WEST));
        ui->left->setText(gameState.getPlayerName(NORTH));
        ui->top->setText(gameState.getPlayerName(EAST));
        ui->right->setText(gameState.getPlayerName(SOUTH));
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

void GameWindow::staticGUIElements()
{
    QPixmap arrowPix(":/resources/guiResources/background/bidBoard.png");
    bidBoard = new QLabel(this);
    bidBoard->setPixmap(arrowPix);
    bidBoard->setGeometry(356,186,1208,708);
    QPixmap playPix(":/resources/guiResources/background/gameBoard.png");
    gameBoard = new QLabel(this);
    gameBoard->setPixmap(playPix);
    gameBoard->setGeometry(356,186,1208,708);
    gameBoard->hide();
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));

    QPixmap XP(":/resources/guiResources/bid/X.png");
    QPixmap XXP(":/resources/guiResources/bid/XX.png");
    QPixmap passP(":/resources/guiResources/bid/PASS.png");
    X = new BidSelect(DOUBLE_BID,this);
    X->setPixmap(XP);
    X->setGeometry(910,600,101,61);
    connect(X,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
    XX = new BidSelect(REDOUBLE_BID,this);
    XX->setPixmap(XXP);
    XX->setGeometry(1060,600,101,61);
    connect(XX,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);
    passB = new BidSelect(PASS,this);
    passB->setPixmap(passP);
    passB->setGeometry(760,600,101,61);
    connect(passB,&BidSelect::sendBidPressed,this,&GameWindow::receiveBid);

    QPixmap tI(":/resources/guiResources/buttons/turn.png");
    turnIndicator = new QLabel(this);
    turnIndicator->setPixmap(tI);
}

void GameWindow::generalError(QString errorMsg)
{
    QMessageBox::warning(this,"Error message",errorMsg);
}

void GameWindow::gameTerminated(QString reason)
{
    QMessageBox::warning(this,"Game terminated",reason);
    this->close();
}

void GameWindow::setName(QString username)
{
    this->name = username;
}

void GameWindow::on_button_exit_clicked()
{
    this->close();
}

void GameWindow::bidRejected(QString reason)
{
    playerMayBid = true;
    QMessageBox::warning(this,"Bid rejected",reason);
}

void GameWindow::moveRejected(QString reason)
{
   playerMayPlay = true;
   QMessageBox::warning(this,"Move rejected",reason);
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
    setWindowIcon(QIcon(":/resources/guiResources/cards/ace_spades.png"));
}
