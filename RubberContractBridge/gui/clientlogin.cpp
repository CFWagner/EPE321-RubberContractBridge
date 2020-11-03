#include "clientlogin.h"
#include "ui_clientlogin.h"

ClientLogin::ClientLogin(QWidget *parent) : QWidget(parent), ui(new Ui::ClientLogin)
{
    ui->setupUi(this);
    networkConnection = new ClientNetwork();
    connect(networkConnection,&ClientNetwork::connectionResult, this,&ClientLogin::connectionResult);
    connect(networkConnection,&ClientNetwork::loginResult, this,&ClientLogin::loginStatus);
    connect(networkConnection,&ClientNetwork::serverDisconnected, this,&ClientLogin::serverDisconnected);
    connect(networkConnection,&ClientNetwork::generalError, this,&ClientLogin::generalError);
    connect(networkConnection,&ClientNetwork::updateGameState, this,&ClientLogin::updateGameState);
    connect(this,&ClientLogin::connectToServer, networkConnection,&ClientNetwork::txRequestLogin);
    setupWindow();
    staticGUIElements();
    this->show();
}

ClientLogin::~ClientLogin()
{
    if(networkConnection != nullptr)
        delete networkConnection;
    if(playerWindow != nullptr)
        delete playerWindow;
    delete ui;
}

void ClientLogin::setupWindow()
{
    QPixmap bkgnd(":/resources/guiResources/background/login.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    this->setFixedSize(415,520);
    this->setWindowTitle ("Rubber Contract Bridge");
    setWindowIcon(QIcon(":/resources/guiResources/cards/ace_spades.png"));
}

void ClientLogin::staticGUIElements()
{
    QPixmap createPixel(":/resources/guiResources/buttons/login_grey.png");
    Hover *loginButton = new Hover(this->pageID,4,this);
    loginButton->setPixmap(createPixel);
    loginButton->setGeometry(130,320,150,64);
    connect(loginButton,&Hover::attemptUserLogin,this,&ClientLogin::attemptLoginButton);
}

void ClientLogin::attemptLoginButton()
{
    int countL = ui->usernameLine->text().length();
    int countS = 0;
    for(int i = 0; i < ui->usernameLine->text().length();i++)
    {
        if (ui->usernameLine->text().at(i) == " ")
        {
            countS++;
        }
    }
    username = ui->usernameLine->text();
    if (username.contains("BOT") == true || username == "" || countS == countL)
    {
        QMessageBox::warning(this,"Login requirments","Your username may not start with BOT or be empty.");
    }
    else
    {
        // The details are read in form the QLineEdits for sending.

        // Set the password
#ifdef QUICK_SERVER_ENTRY
        password = "123@@321";
#endif
#ifndef QUICK_SERVER_ENTRY
        password = ui->passwordLine->text();
#endif

        if (ui->ipAddressLine->text() == ""){
            ipAddress = QHostAddress::LocalHost;
        }
        else
        {
            ipAddress = QHostAddress(ui->ipAddressLine->text());
        }

        if (ui->portLine->text() == ""){
            portID = 61074;
        }
        else
        {
            portID = ui->portLine->text().toUShort();
        }

        emit connectToServer(ipAddress,portID,username,password);
    }
}

void ClientLogin::loginStatus(bool loginSuccessful, QString reason)
{
    if(loginSuccessful == false)
    {
        QMessageBox::warning(this,"Login status",reason);
    }
    else
    {
        QPixmap createPixel(":/resources/guiResources/background/waitScreen.png");
        QLabel *waitLabel = new QLabel(this);
        waitLabel->setPixmap(createPixel);
        waitLabel->setGeometry(0,0,415,520);
        waitLabel->show();
    }
}

void ClientLogin::connectionResult(int status, QString errorMsg)
{
    QString msg;
    switch(status)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        QMessageBox::warning(this,"Login failure",errorMsg);
        break;
    }
    case 3:
    {
        msg = "Already logged in. Nothing was changed.";
        QMessageBox::warning(this,"Login failure",msg);
        break;
    }
    default:
    {
        break;
    }
    }
}

void ClientLogin::serverDisconnected()
{
    QMessageBox::warning(this,"Game started","You have not been picked and the game has started without you.");
    this->close();
}

void ClientLogin::generalError(QString errorMsg)
{
    QMessageBox::warning(this,"Error message",errorMsg);
}

void ClientLogin::updateGameState(PlayerGameState player)
{
    if(player.getEvent() == INITIALIZE)
    {
        playerWindow = new GameWindow(networkConnection);
        playerWindow->setName(username);
        playerWindow->setGameState(player);
        connect(networkConnection,&ClientNetwork::notifyBidTurn, playerWindow,&GameWindow::playerTurnBid);
        disconnect(networkConnection,&ClientNetwork::connectionResult, this,&ClientLogin::connectionResult);
        disconnect(networkConnection,&ClientNetwork::loginResult, this,&ClientLogin::loginStatus);
        disconnect(networkConnection,&ClientNetwork::serverDisconnected, this,&ClientLogin::serverDisconnected);
        disconnect(networkConnection,&ClientNetwork::generalError, this,&ClientLogin::generalError);
        disconnect(networkConnection,&ClientNetwork::updateGameState, this,&ClientLogin::updateGameState);
        disconnect(this,&ClientLogin::connectToServer, networkConnection,&ClientNetwork::txRequestLogin);
        this->close();

    }
}

void ClientLogin::on_infoButton_clicked()
{
    QMessageBox::information(this,"Login requirments","Username may not start with BOT and username must be unique.");
}
