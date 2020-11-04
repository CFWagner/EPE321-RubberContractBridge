#include "logger.h"

/**
 * Constructor, logging is enabled by default.
 * @param parent
 */

Logger::Logger(QObject *parent) : QObject(parent)
{
    // Initialize
    enableLogging = true;
}

/**
 * \brief Enable the logging functionality.
 */

void Logger::enableLog()
{
    enableLogging = true;
}

/**
 * \brief Disable the logging functionality.
 */

void Logger::disableLog()
{
    enableLogging = false;
}

/**
 * \brief Return a boolean. True if logging is enabled.
 */

bool Logger::isLogEnabled() const
{
    return enableLogging;
}
/**
 * \brief Log the data sent to this slot. The time and date is also displayed.
 * \param context QString containing an indication from where the log function was signaled. E.g. AI or GameServer
 * \param msg QString contaiing the message that should be logged.
 */

void Logger::log(QString context, QString msg)
{
    // Check if logging is enabled.
    if (enableLogging == true){
        // Get the local time
        QString logTime = QDateTime::currentDateTimeUtc().toLocalTime().toString("yyyy/MM/dd hh:mm:ss.zzz");

        // Print log to command line
        QTextStream out(stdout);
        out << logTime << " {" << context << "}: " << msg << "\n";

        //Transmit a signal with the logging data.
        emit sendLog(logTime, context, msg);
    }

    // If not enabled, do nothing
}
