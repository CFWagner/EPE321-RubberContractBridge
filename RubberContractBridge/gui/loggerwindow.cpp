#include "loggerwindow.h"
#include "ui_loggerwindow.h"

LoggerWindow::LoggerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggerWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/guiResources/background/LoggerBack.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setStyleSheet("background-color: black;");
    this->setFixedSize(810,720);
    this->setWindowTitle ("Server Logger");
    ui->button_exit->setIcon(QIcon(":/resources/guiResources/buttons/exit_button.png"));
    setWindowIcon(QIcon(":/resources/guiResources/cards/ace_hearts.png"));
    this->show();
}

LoggerWindow::~LoggerWindow()
{
    delete ui;
}

void LoggerWindow::receivedLog(QString logTime, QString context, QString msg)
{
    QString logMessage = logTime + " {" + context + "}: " + msg;
    ui->plainTextEdit->appendPlainText(logMessage);
}

void LoggerWindow::on_button_exit_clicked()
{
    emit closeServerB();
}
