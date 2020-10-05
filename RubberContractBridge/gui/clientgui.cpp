#include "clientgui.h"
#include "ui_clientgui.h"

clientGUI::clientGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientGUI)
{
    ui->setupUi(this);
}

clientGUI::~clientGUI()
{
    delete ui;
}
