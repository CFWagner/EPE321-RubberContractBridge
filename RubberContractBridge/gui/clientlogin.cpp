#include "clientlogin.h"
#include "ui_clientlogin.h"

ClientLogin::ClientLogin(QWidget *parent) : QWidget(parent), ui(new Ui::ClientLogin)
{
    ui->setupUi(this);
    setupWindow();
    staticGUIElements();
    this->show();

}

ClientLogin::~ClientLogin()
{
    delete ui;
}

void ClientLogin::setupWindow()
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

void ClientLogin::staticGUIElements()
{
    QPixmap createPixel(":/resources/guiResources/buttons/login_grey.png");
    Hover *loginButton = new Hover(this->pageID,4,this);
    loginButton->setPixmap(createPixel);
    loginButton->setGeometry(130,320,150,64);
    connect(loginButton,&Hover::attemptUserLogin,this,&ClientLogin::attemptLogin);
}

QString ClientLogin::getUserName()
{
    return username;
}

QString ClientLogin::getPassword()
{
    return password;
}

QHostAddress ClientLogin::getIPAddress()
{
    return ipAddress;
}

quint16 ClientLogin::getPort()
{
    return portID;
}

void ClientLogin::on_infoButton_clicked()
{
    //Gives information on the requirements of login.
    QMessageBox::information(this,"Login requirments","Username may not start with BOT and username must be unique.");

}
void ClientLogin::attemptLogin()
{
    //Checks if the person has chosen an appropriate name for their avatar.
    //Names with BOT in it are not allowed.
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
    this->loginSuccessful = loginSuccessful;
}

void ClientLogin::connectionResult(int status, QString errorMsg)
{
    QString msg;
    if(status == 0)
    {
        msg = errorMsg;
        QMessageBox::information(this,"Client setup",msg);
    }
    else if (status == 1)
    {
        msg = errorMsg;
        QMessageBox::warning(this,"Client setup failure",msg);
    }
    else if (status == 3)
    {
        msg = errorMsg;
        QMessageBox::warning(this,"Server setup failure",msg);
    }
}

void ClientLogin::serverDisconnected()
{
}

