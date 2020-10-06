#include "hover.h"

Hover::Hover(QWidget *parent) : QPushButton(parent)
{
        setMouseTracking(true);
        setAttribute(Qt::WA_Hover);
}

void Hover::hoverEnter(QHoverEvent *)
{
    this->setIcon(QIcon(":/resources/guiResources/background/selectedButton.png"));
    repaint();
}

void Hover::hoverLeave(QHoverEvent *)
{
    this->setIcon(QIcon(":/resources/guiResources/background/unselectedButton.png"));
    repaint();
}

void Hover::hoverMove(QHoverEvent *)
{
    this->setIcon(QIcon(":/resources/guiResources/background/selectedButton.png"));
    repaint();
}

bool Hover::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
