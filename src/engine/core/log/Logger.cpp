#include "engine/core/log/Logger.hpp"

#include <chrono>
#include <iostream>

void Logger::Init()
{
    std::string output;

    output += "===================================================================\n";
    output += "========================= Engine Console ==========================\n";
    output += "===================================================================\n";

    std::cout << output << std::endl;

    LogMessage(LogLevel::Info, "Logger Initialized", __FILE_NAME__, __FUNCTION__, __LINE__);
}

void Logger::Shutdown() {}

void Logger::LogMessage(
    LogLevel level, const std::string &message, const char *file, const char *function, int line
)
{
    std::string output;

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::floor<std::chrono::seconds>(now);

    std::string timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", time);

    // timestamp
    output += "[";
    output += timestamp;
    output += "] ";

    // log level
    output += "[";
    output += LevelToString(level);
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
    std::string color = setLogTextColor(level);

    std::cout << color << output << colorReset << "\n";
}

const char *Logger::LevelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Info:
        return "INFO";

    case LogLevel::Warning:
        return "WARNING";

    case LogLevel::Success:
        return "SUCCESS";

    case LogLevel::Error:
        return "ERROR";

    case LogLevel::Debug:
        return "DEBUG";

    case LogLevel::Trace:
        return "TRACE";
    }

    return "UNKNOWN";
}

const char *Logger::setLogTextColor(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Info:
        return "\033[37m"; // white
    case LogLevel::Warning:
        return "\033[33m"; // yellow
    case LogLevel::Success:
        return "\033[32m"; // green
    case LogLevel::Error:
        return "\033[31m"; // red
    case LogLevel::Debug:
        return "\033[36m"; // cyan
    case LogLevel::Trace:
        return "\033[90m"; // gray
    }
    return "\033[0m";
}
