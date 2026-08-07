#pragma once
#include <format>
#include <string>
#include <string_view>

#include "LogLevel.hpp"

class Logger
{
public:
    static Logger &get()
    {
        static Logger instance;
        return instance;
    }

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void init();
    void shutdown();

    static void
    log(LogLevel level, const char *file, const char *function, int line, std::string_view message)
    {
        get().logImpl(level, std::string(message), file, function, line);
    }

    template <typename... Args>
    static void
    log(LogLevel level,
        const char *file,
        const char *function,
        int line,
        std::format_string<Args...> fmt,
        Args &&...args)
    {
        get().logImpl(level, std::format(fmt, std::forward<Args>(args)...), file, function, line);
    }

private:
    Logger() = default;
    ~Logger() = default;

    void logImpl(
        LogLevel level, const std::string &message, const char *file, const char *function, int line
    );

    constexpr const LogLevelInfo &getLogLevelInfo(LogLevel level)
    {
        return LogLevels[std::to_underlying(level)];
    }
};
