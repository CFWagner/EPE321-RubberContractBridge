#include "clientlogin.h"
#include "ui_clientlogin.h"

clientLogin::clientLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientLogin)
{
    ui->setupUi(this);
    windowSetup();
    this->show();
}

clientLogin::~clientLogin()
{
    delete ui;
}

void clientLogin::windowSetup()
{
    QPixmap bkgnd(":/resources/guiResources/background/login.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(415,520);
    QWidget::setWindowTitle ("Login Screen");
    ui->loginButton->setIcon(QIcon(":/resources/guiResources/background/unselectedButton.png"));
    ui->usernameLabel->setStyleSheet("color: white;font: bold");
    ui->passwordLabel->setStyleSheet("color: white;font: bold");
    ui->loginBox->setStyleSheet("color: white;font: bold");
}

void clientLogin::on_loginButton_clicked()
{
    attemptLogin();
}

void clientLogin::on_infoButton_clicked()
{
   QMessageBox::information(this,"Login requirments","Username may not start with BOT and username must be unique.");

}
void clientLogin::attemptLogin()
{
    username = ui->userNameLine->text();
    if (username.contains("BOT") == true)
    {
        QMessageBox::warning(this,"Login requirments","Username may not start with BOT and username must be unique.");
    }
    else
    {
        password = ui->passwordLines->text();
        ipAddress = QHostAddress(ui->ipAddressLine->text());
        portID = ui->portLine->text().toUShort();
        emit connectToServer(ipAddress,portID,password,username);
    }
}
