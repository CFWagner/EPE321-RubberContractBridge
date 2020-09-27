#ifndef PLAYERNETWORK_H
#define PLAYERNETWORK_H

#include <QObject>

class PlayerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit PlayerNetwork(QObject *parent = nullptr);

signals:

};

#endif // PLAYERNETWORK_H
