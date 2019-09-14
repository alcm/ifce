#include "logger.h"

#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger()
{
    qRegisterMetaType<std::string>("std::string");
}

void Logger::Log(const std::string &msg)
{
    std::time_t t = std::time(nullptr);
    std::stringstream formatted_msg;

    formatted_msg << std::put_time(std::localtime(&t), "%T") << ": " << msg;

    emit SendMsg(formatted_msg.str());
}
