#include <iostream>
#include <string>

class Logger {
   public:
    static Logger *instance()
    {
        static Logger instance;

        return &instance;
    }

    void Log(const std::string &msg)
    {
        std::cout << msg << std::endl;
    }

   private:
    Logger()
    {
        std::cout << "Constructor" << std::endl;
    }
};

int main()
{
    auto logger = Logger::instance();

    logger->Log("Hello, world!");
}
