
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <string>

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger();

    void Log(const std::string &msg);

signals:
    void SendMsg(const std::string &msg);

public slots:
};

#endif // LOGGER_H
