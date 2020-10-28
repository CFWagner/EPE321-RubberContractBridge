#ifndef PLAYCARDSELECTED_H
#define PLAYCARDSELECTED_H

#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class PlayCardSelected : public QLabel
{
    Q_OBJECT
public:
    explicit PlayCardSelected(QWidget *parent = nullptr);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
signals:
    void sendCardPlayed(PlayCardSelected *);

};

#endif // PLAYCARDSELECTED_H
