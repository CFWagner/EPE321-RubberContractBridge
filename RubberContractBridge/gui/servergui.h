#ifndef SERVERGUI_H
#define SERVERGUI_H

#include <QWidget>

namespace Ui {
class serverGUI;
}

class serverGUI : public QWidget
{
    Q_OBJECT

public:
    explicit serverGUI(QWidget *parent = nullptr);
    ~serverGUI();

private:
    Ui::serverGUI *ui;
};

#endif // SERVERGUI_H
