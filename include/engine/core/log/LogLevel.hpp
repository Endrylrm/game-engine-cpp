#pragma once
#include <array>

enum class LogLevel
{
    Trace,
    Debug,
    Info,
    Success,
    Warning,
    Error,
    Critical
};

struct LogLevelInfo
{
    std::string_view name;
    std::string_view color;
};

constexpr std::array<LogLevelInfo, 7> LogLevels{
    {{"TRACE", "\033[90m"},
     {"DEBUG", "\033[36m"},
     {"INFO", "\033[37m"},
     {"SUCCESS", "\033[32m"},
     {"WARNING", "\033[33m"},
     {"ERROR", "\033[31m"},
     {"CRITICAL", "\033[1;91m"}}
};
