#include "serverlobby.h"
#include "ui_serverlobby.h"

ServerLobby::ServerLobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerLobby)
{
    ui->setupUi(this);
    this->show();
}

ServerLobby::~ServerLobby()
{
    delete ui;
}
