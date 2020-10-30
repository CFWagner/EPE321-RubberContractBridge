#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include "hover.h"
#include "game-server/server.h"
#include <QWidget>

namespace Ui {class EntryWindow;}

class EntryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();
    void setupWindow();
    void staticGUIElements();

public slots:
    void gotoServer();
    void goClientLogin();

private:
    Ui::EntryWindow *ui;
    int pageID = 0;
    Server *createdServer;
};

#endif // ENTRYWINDOW_H
