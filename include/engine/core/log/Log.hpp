#pragma once

#include "engine/core/log/Logger.hpp"

#define LOG(level, ...) Logger::Log(level, __FILE_NAME__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define LOG_INFO(...) LOG(LogLevel::Info, __VA_ARGS__)
#define LOG_WARNING(...) LOG(LogLevel::Warning, __VA_ARGS__)
#define LOG_SUCCESS(...) LOG(LogLevel::Success, __VA_ARGS__)
#define LOG_ERROR(...) LOG(LogLevel::Error, __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LogLevel::Debug, __VA_ARGS__)
#define LOG_TRACE(...) LOG(LogLevel::Trace, __VA_ARGS__)
