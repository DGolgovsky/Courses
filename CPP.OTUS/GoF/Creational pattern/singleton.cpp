// Одиночка (Singleton)

#include <iostream>

class Logger
{
public:
    static Logger& Instance()
    {
        static Logger instance;
        return instance;
    }
    void info(const std::string &message)
    {
        std::cerr << "   info: " << message << std::endl;
    }
    void warn(const std::string &message)
    {
        std::cerr << "warning: " << message << std::endl;
    }
private:
    Logger() = default;
    Logger(const Logger& root) = delete;
    Logger& operator=(const Logger&) = delete;
};

int main(int, char const **)
{
    Logger::Instance().info("started");
    Logger::Instance().warn("program is empty");

    return 0;
}
