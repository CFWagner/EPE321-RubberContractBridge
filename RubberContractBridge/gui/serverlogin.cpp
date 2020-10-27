#include "serverlogin.h"
#include "ui_serverlogin.h"

ServerLogin::ServerLogin(QWidget *parent) : QWidget(parent), ui(new Ui::ServerLogin)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
    this->show();
}

ServerLogin::~ServerLogin()
{
    delete ui;
}

void ServerLogin::setupWindow()
{
    // QPixmap maps the pixels of the background fot the palatte to brush it onto the
    // current ui.
    QPixmap bkgnd(":/resources/guiResources/background/login.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //Fix the size of the window to a specified 415 by 520 ratio (16:12)
    this->setFixedSize(415,520);
    this->setWindowTitle ("Rubber Contract Bridge");
}

void ServerLogin::staticGUIElements()
{
    QPixmap createPixel(":/resources/guiResources/buttons/create_grey.png");
    Hover *createServerB = new Hover(this->pageID,3,this);
    createServerB->setPixmap(createPixel);
    createServerB->setGeometry(130,320,150,64);

    // If button is pressed I try and connect.
    connect(createServerB,&Hover::attemptConnect,this,&ServerLogin::tryConnect);
}

void ServerLogin::tryConnect()
{
    // First check if the password is strong enough.
    bool validPassword = checkValidPassword();
    if (validPassword == true)
    {
        // If the IP address or port isn't given then set it as default.
        if(ui->ipLine->text() == "" || ui->portLine->text() == "")
        {
            ipAddress = QHostAddress::LocalHost;
            portID = 61074;
        }
        else
        {
            ipAddress = QHostAddress(ui->ipLine->text());
            portID = ui->portLine->text().toUShort();
        }
        serverLob = new ServerLobby();
        this->close();
        //        connect(this,&ServerLogin::sendServerPassword,serverCreated,&Server::serverPassword);
        //        connect(this,&ServerLogin::sendIPAddressPort,serverCreated,&Server::serverIPAddressPort);
        emit serverPassword(password);
        emit serverIPAddressPort(ipAddress,portID);

    }

}

void ServerLogin::connectionResult(int status, QHostAddress ip, quint16 port, QString errorMsg)
{
    // Once the server Password and IPAddress is sent the network will notify the GUI that it was successful,
    //in creating the server.
    QString msg = "";
    if(status == 0)
    {
        //serverLob = new ServerLobby();
        //this->close();
    }
    else if (status == 1)
    {
        msg = "Invalid IP-Address";
        QMessageBox::warning(this,"Server setup failure",msg);
    }
    else if (status == 2)
    {
        msg = errorMsg;
        QMessageBox::warning(this,"Server setup failure",msg);
    }
    else if (status == 3)
    {
        msg = "The server can only be initialized once. Nothing was changed.";
        QMessageBox::warning(this,"Server setup failure",msg);
    }
}

void ServerLogin::generalError(QString errorMsg)
{
    //General errors may occure.
    QMessageBox::warning(this,"Error message",errorMsg);
}

QString ServerLogin::getPassword()
{
    return password;
}

QHostAddress ServerLogin::getIPAddress()
{
    return ipAddress;
}

quint16 ServerLogin::getPort()
{
    return portID;
}

bool ServerLogin::checkValidPassword()
{
    // Checks if the password is valid, it must contain one of the characters below and must
    // be 8 characters long.
    password = ui->passswordLine->text();
    bool validPassword = false;
    char array [9] = {'!','@','#','$','%','^','&','*','?'};
    if (password.length() >= 8)
    {
        for (int i = 0; i < password.length();i++)
        {
            if (password.contains(array[i]) == true)
            {
                validPassword = true;
            }
        }
    }
    //If invalid the message will notify the user and the signal will not be sent.
    if(validPassword == false)
    {
        password="INVALID";
        QMessageBox::warning(this,"Password invalid","Server password is too weak try another one that has atleast 8 characters long and contains atleast 1 special character.");
    }
    return validPassword;
}
