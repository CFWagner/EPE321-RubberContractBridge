#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{
    // Initialize
    enableLogging = true;
}

void Logger::enableLog()
{
    enableLogging = true;
}

void Logger::disableLog()
{
    enableLogging = false;
}

bool Logger::isLogEnabled() const
{
    return enableLogging;
}

void Logger::log(QString context, QString msg)
{
    // Show that a log was signal was emitted
    qDebug() << "Logger::log (enableLogging:" << isLogEnabled() << ") Context:" << context << "Message:" << msg;

    // Check if logging is enabled.
    if (enableLogging == true){
        // Get the local time
        QDateTime UTC(QDateTime::currentDateTimeUtc());
        QDateTime local(UTC.toLocalTime());

        // Print log to command line
        // qDebug() << QLocale().toString(local, QLocale::ShortFormat) <<" {" << context << "}: " << msg;
        QTextStream out(stdout);
        out << QLocale().toString(local, QLocale::ShortFormat) <<" {" << context << "}: " << msg << "\n";

        //Transmit a signal with the logging data.
        emit sendLog(context,msg);
    }
    // If not enabled, do noting
}
