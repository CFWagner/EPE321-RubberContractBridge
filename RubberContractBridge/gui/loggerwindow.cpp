#include "loggerwindow.h"
#include "ui_loggerwindow.h"

LoggerWindow::LoggerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggerWindow)
{
    ui->setupUi(this);
    this->show();
}

LoggerWindow::~LoggerWindow()
{
    delete ui;
}

void LoggerWindow::receivedLog(QString time, QString context, QString reason)
{

}
