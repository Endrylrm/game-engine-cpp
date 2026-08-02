#pragma once

#include <format>
#include <string>
#include <string_view>

enum class LogLevel
{
    Info,
    Warning,
    Success,
    Error,
    Debug,
    Trace
};

class Logger
{
public:
    static void Init();
    static void Shutdown();

    static void
    Log(LogLevel level, const char *file, const char *function, int line, std::string_view message)
    {
        LogMessage(level, std::string(message), file, function, line);
    }

    template <typename... Args>
    static void
    Log(LogLevel level,
        const char *file,
        const char *function,
        int line,
        std::format_string<Args...> fmt,
        Args &&...args)
    {
        LogMessage(level, std::format(fmt, std::forward<Args>(args)...), file, function, line);
    }

private:
    static void LogMessage(
        LogLevel level, const std::string &message, const char *file, const char *function, int line
    );

    static const char *LevelToString(LogLevel level);
    static const char *setLogTextColor(LogLevel level);
};
