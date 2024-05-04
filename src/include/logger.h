#pragma once

#include "lockqueue.h"

enum LogLevel
{
    INFO,  // 普通日志信息
    ERROR, // 错误信息
};

// Mprpc 框架提供的日志系统
class Logger{
public:
    // 获取日志单例
    static Logger &GetInstance();

    void SetLogLevel(LogLevel level);
    void Log(std::string msg);

private:
    LogLevel m_loglevel;
    LockQueue<std::string> m_lckQue;        // 日志缓冲队列
    Logger();
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
};

#define LOG_INFO(logmsgformat, ...)                 \
    do                                              \
    {                                               \
        Logger &logger = Logger::GetInstance();     \
        logger.SetLogLevel(INFO);                   \
        char c[1024] = {0};                         \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);  \
        logger.Log(c);                              \
    }while (0);     

#define LOG_ERR(logmsgformat, ...)                 \
    do                                              \
    {                                               \
        Logger &logger = Logger::GetInstance();     \
        logger.SetLogLevel(ERROR);                   \
        char c[1024] = {0};                         \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);  \
        logger.Log(c);                              \
    }while (0);         
                              