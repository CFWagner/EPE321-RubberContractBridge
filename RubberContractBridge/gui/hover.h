#ifndef HOVER_H
#define HOVER_H

#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class Hover : public QLabel
{
    Q_OBJECT

public:
    explicit Hover(int pageID,int elementID, QWidget *parent = 0);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void serverSelected();
    void gotoClientLogin();
    void attemptConnect();
    void attemptUserLogin();
    void addPlayersLobby();
    void clearPlayersLobby();
    void startGameB();
private:
    int pageID;
    int elementID;
    QWidget *parent;
};

#endif // HOVER_H
