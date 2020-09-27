#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::enableLog()
{

}

void Logger::disableLog()
{

}

bool Logger::isLogEnabled() const
{
    return enableLogging;
}

void Logger::log(QString context, QString msg)
{

}
