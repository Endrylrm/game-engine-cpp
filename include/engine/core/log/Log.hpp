#pragma once

#include "engine/core/log/Logger.hpp"

#define LOG_INIT() Logger::Init()
#define LOG_INFO(...) Logger::Log(LogLevel::Info, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) Logger::Log(LogLevel::Warning, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::Log(LogLevel::Error, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::Log(LogLevel::Debug, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_TRACE(...) Logger::Log(LogLevel::Trace, __FILE_NAME__, __LINE__, __VA_ARGS__)
