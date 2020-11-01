#include "hover.h"

Hover::Hover(int pageID,int elementID,QWidget *parent) : QLabel(parent)
{
    this->pageID = pageID;
    this->elementID = elementID;
    this->parent = parent;
}

void Hover::enterEvent(QEvent *)
{
    switch (elementID)
    {
    case 1:
    {
        QPixmap pix(":/resources/guiResources/buttons/s_green.png");
        this->setPixmap(pix);
        break;
    }
    case 2:
    {
        QPixmap pix(":/resources/guiResources/buttons/c_green.png");
        this->setPixmap(pix);
        break;
    }
    case 3:
    {
        QPixmap pix(":/resources/guiResources/buttons/create_green.png");
        this->setPixmap(pix);
        break;
    }
    case 4:
    {
        QPixmap pix(":/resources/guiResources/buttons/login_green.png");
        this->setPixmap(pix);
        break;
    }
    case 5:
    {
        QPixmap pix(":/resources/guiResources/buttons/add_green.png");
        this->setPixmap(pix);
        break;
    }
    case 6:
    {
        QPixmap pix(":/resources/guiResources/buttons/clear_green.png");
        this->setPixmap(pix);
        break;
    }
    case 7:
    {
        QPixmap pix(":/resources/guiResources/buttons/start_green.png");
        this->setPixmap(pix);
        break;
    }
    default:
        break;
    }
}

void Hover::leaveEvent(QEvent *)
{
    switch (elementID)
    {
    case 1:
    {
        QPixmap pix(":/resources/guiResources/buttons/s_grey.png");
        this->setPixmap(pix);
        break;
    }
    case 2:
    {
        QPixmap pix(":/resources/guiResources/buttons/c_grey.png");
        this->setPixmap(pix);
        break;
    }
    case 3:
    {
        QPixmap pix(":/resources/guiResources/buttons/create_grey.png");
        this->setPixmap(pix);
        break;
    }
    case 4:
    {
        QPixmap pix(":/resources/guiResources/buttons/login_grey.png");
        this->setPixmap(pix);
        break;
    }
    case 5:
    {
        QPixmap pix(":/resources/guiResources/buttons/add_grey.png");
        this->setPixmap(pix);
        break;
    }
    case 6:
    {
        QPixmap pix(":/resources/guiResources/buttons/clear_grey.png");
        this->setPixmap(pix);
        break;
    }
    case 7:
    {
        QPixmap pix(":/resources/guiResources/buttons/start_grey.png");
        this->setPixmap(pix);
        break;
    }
    default:
        break;
    }
}

void Hover::mousePressEvent(QMouseEvent *)
{
    switch (elementID)
    {
    case 1:
    {
        emit serverSelected();
        break;
    }
    case 2:
    {
        emit gotoClientLogin();
        break;
    }
    case 3:
    {
        emit attemptConnect();
        break;
    }
    case 4:
    {
        emit attemptUserLogin();
        break;
    }
    case 5:
    {
        emit addPlayersLobby();
        break;
    }
    case 6:
    {
        emit clearPlayersLobby();
        break;
    }
    case 7:
    {
        emit startGameB();
        break;
    }
    default:
        break;
    }
}
