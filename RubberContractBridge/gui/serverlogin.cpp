#include "serverlogin.h"
#include "ui_serverlogin.h"

ServerLogin::ServerLogin(QWidget *parent) : QWidget(parent), ui(new Ui::ServerLogin)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
    serverCreated = new Server();
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
            portID = defaultPort;
        }
        else
        {
            ipAddress = QHostAddress(ui->ipLine->text());
            portID = ui->portLine->text().toUShort();
        }
        this->close();
        ServerLobby *serverLobby = new ServerLobby(serverCreated);
        connect(this,&ServerLogin::sendServerPassword,serverCreated,&Server::serverPassword);
        connect(this,&ServerLogin::sendIPAddressPort,serverCreated,&Server::serverIPAddressPort);
        emit sendServerPassword(password);
        emit sendIPAddressPort(ipAddress,portID);

    }

}

void ServerLogin::connectionResult(int status, QHostAddress ip, quint16 port, QString errorMsg)
{

}

void ServerLogin::generalError(QString errorMsg)
{

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
