#include "loggerwindow.h"
#include "ui_loggerwindow.h"

LoggerWindow::LoggerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggerWindow)
{
    ui->setupUi(this);
}

LoggerWindow::~LoggerWindow()
{
    delete ui;
    this->show();
}
