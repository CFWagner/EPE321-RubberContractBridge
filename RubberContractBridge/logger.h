#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    void enableLog();
    void disableLog();
    bool isLogEnabled() const;

signals:
    void sendLog (QString context, QString msg) const;


private slots:
    void log(QString context, QString msg);

private:
    bool enableLogging;

};

#endif // LOGGER_H
