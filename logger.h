#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    static void log(const std::string& event) {
        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            std::tm* localTime = std::localtime(&now);

            logFile << "[" << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << "] " << event << std::endl;
            logFile.close();
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() = default;
    ~Logger() = default;
};

#define LOG_EVENT(event) Logger::getInstance().log(event)