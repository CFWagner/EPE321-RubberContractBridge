#include "servergui.h"
#include "ui_servergui.h"

serverGUI::serverGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverGUI)
{
    ui->setupUi(this);
}

serverGUI::~serverGUI()
{
    delete ui;
}
