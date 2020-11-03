#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>
#include <QTextStream>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    void enableLog();
    void disableLog();
    bool isLogEnabled() const;

signals:
    void sendLog (QString logTime, QString context, QString msg) const;

public slots:
    void log(QString context, QString msg);

private:
    bool enableLogging;

};

#endif // LOGGER_H
