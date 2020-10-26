#include "hover.h"

Hover::Hover(int pageID,int elementID,QWidget *parent) : QLabel(parent)
{
    this->pageID = pageID;
    this->elementID = elementID;
    this->parent = parent;
}

void Hover::enterEvent(QEvent *event)
{
    if (this->elementID == 1)
    {
        QPixmap pix(":/resources/guiResources/buttons/s_green.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 2)
    {
        QPixmap pix(":/resources/guiResources/buttons/c_green.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 3)
    {
        QPixmap pix(":/resources/guiResources/buttons/create_green.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 4)
    {
        QPixmap pix(":/resources/guiResources/buttons/login_green.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 5)
    {
        QPixmap pix(":/resources/guiResources/buttons/add_green.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 6)
    {
        QPixmap pix(":/resources/guiResources/buttons/clear_green.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 7)
    {
        QPixmap pix(":/resources/guiResources/buttons/start_green.png");
        this->setPixmap(pix);
    }
}

void Hover::leaveEvent(QEvent *event)
{
    if (this->elementID == 1)
    {
        QPixmap pix(":/resources/guiResources/buttons/s_grey.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 2)
    {
        QPixmap pix(":/resources/guiResources/buttons/c_grey.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 3)
    {
        QPixmap pix(":/resources/guiResources/buttons/create_grey.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 4)
    {
        QPixmap pix(":/resources/guiResources/buttons/login_grey.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 5)
    {
        QPixmap pix(":/resources/guiResources/buttons/add_grey.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 6)
    {
        QPixmap pix(":/resources/guiResources/buttons/clear_grey.png");
        this->setPixmap(pix);
    }
    else if (this->elementID == 7)
    {
        QPixmap pix(":/resources/guiResources/buttons/start_grey.png");
        this->setPixmap(pix);
    }
}

void Hover::mousePressEvent(QMouseEvent *event)
{
    if (this->elementID == 1)
    {
        ServerLogin *serverLogin = new ServerLogin();
        parent->close();
    }
    else if (this->elementID == 2)
    {
        ClientLogin *clientLogin = new ClientLogin();
        parent->close();
    }
    else if (this->elementID == 3)
    {
        emit attemptConnect();
    }
    else if (this->elementID == 4)
    {
        emit attemptUserLogin();
    }
    else if (this->elementID == 5)
    {
        emit addPlayersLobby();
    }
    else if (this->elementID == 6)
    {
        emit clearPlayersLobby();
    }
    else if (this->elementID == 7)
    {
        emit startGameB();
    }
}
