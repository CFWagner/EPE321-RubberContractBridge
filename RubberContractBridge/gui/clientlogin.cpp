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
    connect(this,&ClientLogin::connectToServer, networkConnection,&ClientNetwork::txRequestLogin);
    setupWindow();
    staticGUIElements();
    this->show();
}

ClientLogin::~ClientLogin()
{
    if(networkConnection != nullptr)
        delete networkConnection;
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
    username = ui->usernameLine->text();
    if (username.contains("BOT") == true || username == "")
    {
        QMessageBox::warning(this,"Login requirments","Your username may not start with BOT or be empty.");
    }
    else
    {
        // The details are read in form the QLineEdits for sending.
        password = ui->passwordLine->text();
        ipAddress = QHostAddress(ui->ipAddressLine->text());
        portID = ui->portLine->text().toUShort();
        emit connectToServer(ipAddress,portID,username,password);
    }
}

void ClientLogin::loginStatus(bool loginSuccessful, QString reason)
{
    if(loginSuccessful == false)
    {
        QMessageBox::warning(this,"Login status",reason);
    }
}

void ClientLogin::connectionResult(int status, QString errorMsg)
{
    QString msg;
    switch(status)
    {
    case 0:
    {
        //this->close();
        qDebug() << status;
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
    QMessageBox::warning(this,"Game started","Game has started");
}

void ClientLogin::generalError(QString errorMsg)
{
    QMessageBox::warning(this,"Error message",errorMsg);
}

void ClientLogin::on_infoButton_clicked()
{
    QMessageBox::information(this,"Login requirments","Username may not start with BOT and username must be unique.");
}
