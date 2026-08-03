#pragma once
#include "engine/core/log/Logger.hpp"

#define LOG_TRACE(...)                                                                             \
    Logger::log(LogLevel::Trace, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...)                                                                             \
    Logger::log(LogLevel::Debug, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)                                                                              \
    Logger::log(LogLevel::Info, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_SUCCESS(...)                                                                           \
    Logger::log(LogLevel::Success, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...)                                                                           \
    Logger::log(LogLevel::Warning, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...)                                                                             \
    Logger::log(LogLevel::Error, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_CRITICAL(...)                                                                          \
    Logger::log(LogLevel::Critical, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
