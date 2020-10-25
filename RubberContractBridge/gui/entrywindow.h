#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include "hover.h"
#include <QWidget>
#include <QDebug>

namespace Ui {
class EntryWindow;
}

class EntryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();
    void setupWindow();
    void staticGUIElements();

private:
    Ui::EntryWindow *ui;
    int pageID = 0;
};

#endif // ENTRYWINDOW_H
