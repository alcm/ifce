/**
 * \file
 * \brief  Logger definition.
 */
#ifndef LOGGER_H_
#define LOGGER_H_

#include <QObject>

#include <string>

/**
 * \brief  Logger class definition.
 */
class Logger : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief  Constructor.
     */
    Logger();

    /**
     * \brief  Log a message to user interface.
     * \param  msg Message to be logged.
     */
    void Log(const std::string &msg);

signals:
    /**
     * \brief  Send message signal.
     * \param  msg Message to be sent.
     */
    void SendMsg(const std::string &msg);
};

#endif // LOGGER_H_
