#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include <QObject>

class ServerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ServerNetwork(QObject *parent = nullptr);

signals:

};

#endif // SERVERNETWORK_H
