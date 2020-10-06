#ifndef CLIENTLOGINGUI_H
#define CLIENTLOGINGUI_H

#include <QWidget>

namespace Ui {
class clientLoginGUI;
}

class clientLoginGUI : public QWidget
{
    Q_OBJECT

public:
    explicit clientLoginGUI(QWidget *parent = nullptr);
    ~clientLoginGUI();

private slots:
    void on_loginButton_clicked();
    void on_infoButton_clicked();

private:
    Ui::clientLoginGUI *ui;
};

#endif // CLIENTLOGINGUI_H
