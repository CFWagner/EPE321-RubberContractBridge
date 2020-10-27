#include "bidwindow.h"
#include "ui_bidwindow.h"

BidWindow::BidWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BidWindow)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
    this->showFullScreen();
}

BidWindow::~BidWindow()
{
    qDebug()<<"Exit";
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

void BidWindow::staticGUIElements()
{
    QPixmap arrowPix(":/resources/guiResources/bid/arrows.png");
    ui->label->setPixmap(arrowPix);
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));
    ui->you->setText("NORTH");
    ui->right->setText("WEST");
    ui->left->setText("EAST");
    ui->top->setText("SOUTH");
}





void BidWindow::on_button_exit_clicked()
{
    this->close();
}

void BidWindow::getUpdateGameState(PlayerGameState player)
{
    this->player = player;
    qDebug() <<"A";
}


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

    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(DIAMONDS,i+1,this);
        bidCards[i+7] = bidCard;
        cardName = imageName + "diamond_"+QString::number(i+1)+".png)";
        bidCards[i+7]->setStyleSheet(cardName);
        bidCards[i+7]->setGeometry(920,300+30*i,61,101);
    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(HEARTS,i+1,this);
        bidCards[i+14] = bidCard;
        cardName = imageName + "heart_"+QString::number(i+1)+".png)";
        bidCards[i+14]->setStyleSheet(cardName);
        bidCards[i+14]->setGeometry(820,300+30*i,61,101);
    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(SPADES,i+1,this);
        bidCards[i+21] = bidCard;
        cardName = imageName + "spade_"+QString::number(i+1)+".png)";
        bidCards[i+21]->setStyleSheet(cardName);
        bidCards[i+21]->setGeometry(720,300+30*i,61,101);
    }
    for (int i = 0; i < 7;i++)
    {
        bidCard = new BidCardsSelected(NONE,i+1,this);
        bidCards[i+28] = bidCard;
        cardName = imageName + "NT_"+QString::number(i+1)+".png)";
        bidCards[i+28]->setStyleSheet(cardName);
        bidCards[i+28]->setGeometry(620,300+30*i,61,101);
    }
}
