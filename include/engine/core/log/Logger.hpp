#pragma once

#include <format>
#include <string>
#include <string_view>

enum class LogLevel
{
    Info,
    Warning,
    Error,
    Debug,
    Trace
};

class Logger
{
public:
    static void Init();
    static void Shutdown();

    static void Log(LogLevel level, const char *file, int line, std::string_view message)
    {
        LogMessage(level, std::string(message), file, line);
    }

    template <typename... Args>
    static void
    Log(LogLevel level, const char *file, int line, std::format_string<Args...> fmt, Args &&...args)
    {
        LogMessage(level, std::format(fmt, std::forward<Args>(args)...), file, line);
    }

private:
    static void LogMessage(LogLevel level, const std::string &message, const char *file, int line);

    static const char *LevelToString(LogLevel level);
    static const char *setLogTextColor(LogLevel level);
};
