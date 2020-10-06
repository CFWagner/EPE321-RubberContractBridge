#ifndef HOVER_H
#define HOVER_H

#include <QtWidgets>

class Hover : public QPushButton
{
    Q_OBJECT
public:
    explicit Hover(QWidget *parent = 0);

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:

public slots:
};

#endif // HOVER_H
