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
        get().log_impl(level, std::string(message), file, function, line);
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
        get().log_impl(level, std::format(fmt, std::forward<Args>(args)...), file, function, line);
    }

private:
    Logger() = default;
    ~Logger() = default;

    void log_impl(
        LogLevel level, const std::string &message, const char *file, const char *function, int line
    );

    constexpr const LogLevelInfo &get_log_level_info(LogLevel level)
    {
        return LOG_LEVELS[std::to_underlying(level)];
    }
};
