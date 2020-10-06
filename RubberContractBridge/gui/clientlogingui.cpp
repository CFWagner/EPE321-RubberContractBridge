#include "clientlogingui.h"
#include "ui_clientlogingui.h"

clientLoginGUI::clientLoginGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientLoginGUI)
{
    ui->setupUi(this);
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

clientLoginGUI::~clientLoginGUI()
{
    delete ui;
}

void clientLoginGUI::on_loginButton_clicked()
{
    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();
    qDebug() << username;
    qDebug() << password;
}

void clientLoginGUI::on_infoButton_clicked()
{
   QMessageBox::information(this,"Login requirments","Username may not start with BOT and username must be unique.");

}
