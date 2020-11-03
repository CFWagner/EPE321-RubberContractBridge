#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QWidget>
#include <QTextStream>
#include "logger/logger.h"
namespace Ui {
class LoggerWindow;
}

class LoggerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoggerWindow(QWidget *parent = nullptr);
    ~LoggerWindow();
public slots:
    void receivedLog(QString logTime, QString context, QString msg);
private:
    Ui::LoggerWindow *ui;
};

#endif // LOGGERWINDOW_H
