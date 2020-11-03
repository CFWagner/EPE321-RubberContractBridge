#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QWidget>
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

private:
    Ui::LoggerWindow *ui;
};

#endif // LOGGERWINDOW_H
