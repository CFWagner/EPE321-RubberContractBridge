#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(ClientNetwork *clientNetwork, QWidget *parent) : QWidget(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->clientNetwork = clientNetwork;
    connect(clientNetwork,&ClientNetwork::updateGameState, this,&GameWindow::updateGameState);
    connect(clientNetwork,&ClientNetwork::generalError, this,&GameWindow::generalError);
    connect(clientNetwork,&ClientNetwork::gameTerminated, this,&GameWindow::gameTerminated);
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
}

void GameWindow::updateGameState(PlayerGameState gameState)
{
    this->gameState = gameState;
    qDebug() <<"WOOP" << gameState.getEvent();

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

void GameWindow::on_button_exit_clicked()
{
    this->close();
}
