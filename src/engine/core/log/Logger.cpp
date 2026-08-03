#include "engine/core/log/Logger.hpp"

#include <chrono>
#include <iostream>

void Logger::init()
{
    std::string output;

    output += "===================================================================\n";
    output += "========================= Engine Console ==========================\n";
    output += "===================================================================\n";

    std::cout << output << std::endl;

    log(LogLevel::Info, __FILE_NAME__, __FUNCTION__, __LINE__, "Logger Initialized");
}

void Logger::shutdown() {}

void Logger::logImpl(
    LogLevel level, const std::string &message, const char *file, const char *function, int line
)
{
    std::string output;

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::floor<std::chrono::seconds>(now);

    std::string timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", time);

    const auto &info = getLogLevelInfo(level);

    // timestamp
    output += "[";
    output += timestamp;
    output += "] ";

    // log level
    output += "[";
    output += info.name;
    output += "] ";

    // file and line
    output += file;
    output += ":";
    output += std::to_string(line);

    // function
    output += " - ";
    output += function;

    // message
    output += " - ";
    output += message;

    std::string colorReset = "\033[0m";

    std::cout << info.color << output << colorReset << "\n";
}
