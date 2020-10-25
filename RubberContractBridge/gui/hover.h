#ifndef HOVER_H
#define HOVER_H

#include "serverlogin.h"
#include "clientlogin.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class Hover : public QLabel
{
    Q_OBJECT
public:
    explicit Hover(int,int, QWidget *parent = 0);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
signals:
    void attemptConnect();
    void attemptUserLogin();
private:
    int pageID;
    int elementID;
    QWidget *parent;
};

#endif // HOVER_H
