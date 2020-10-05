#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QWidget>

namespace Ui {
class clientGUI;
}

class clientGUI : public QWidget
{
    Q_OBJECT

public:
    explicit clientGUI(QWidget *parent = nullptr);
    ~clientGUI();

private:
    Ui::clientGUI *ui;
};

#endif // CLIENTGUI_H
