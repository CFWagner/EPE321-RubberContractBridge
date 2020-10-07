#include "servergui.h"
#include "ui_servergui.h"

ServerGUI::ServerGUI(QWidget *parent) :QWidget(parent),ui(new Ui::ServerGUI)
{
    ui->setupUi(this);
    windowSetup();
    this->show();

}

ServerGUI::~ServerGUI()
{
    delete ui;
}

void ServerGUI::windowSetup()
{
    //Set up the background pixelmap
    QPixmap background(":/resources/guiResources/background/login.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    //Draw the background into the desired size.
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    //Specify size.
    this->setFixedSize(415,520);
    ServerGUI::setWindowTitle ("Rubber Contract Bridge");
    ui->serverSetupButton->setIcon(QIcon(":/resources/guiResources/background/unselectedButton.png"));
}

void ServerGUI::connectionResults(int status, QHostAddress ipAddress, quint16 port, QString errorMsg)
{
    QString msg = "";
    if(status == 0)
    {
        this->close();
    }
    else if (status == 0)
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

void ServerGUI::generalInfo(QString infoMsg)
{
    QMessageBox::information(this,"Connection status",infoMsg);
}

void ServerGUI::generalError(QString errorMsg)
{
    QMessageBox::warning(this,"Error message",errorMsg);
}

void ServerGUI::on_serverSetupButton_clicked()
{
    attemptLogin();
}

void ServerGUI::attemptLogin()
{
    bool validPassword = checkValidPassword();
    if (validPassword == true)
    {
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
        emit setPassword(password);
        emit sendServerDetails(ipAddress,portID);
        this->close();
        lobbyWindow = new serverLobby();
    }
        emit setPassword(password);
}
bool ServerGUI::checkValidPassword()
{
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
    if(validPassword == false)
    {
        password="INVALID";
        QMessageBox::warning(this,"Password invalid","Server password is too weak try another one that has atleast 8 characters and contains atleast 1 special character.");
    }
    return validPassword;
}
