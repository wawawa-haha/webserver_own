#ifndef _LOG_H
#define _LOG_H
#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
namespace sm{
//每个日志出现，当作一个Logevent
enum class Level{
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4
};
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent() = default;
public:
    //与构造函数使用初始化成员列表一样
    const char* m_file = nullptr;
    int32_t m_line = 0;
    uint32_t elapse = 0;
    uint32_t m_threadID = 0;
    uint32_t m_fiberID = 0;
    uint64_t m_time;
    std::string m_content;
};

//日志格式器
class LogFromatter{
public:
    typedef std::shared_ptr<LogFromatter> ptr;
    std::string format(LogEvent::ptr event);
    LogFromatter ()= default;
private:
};

//日志输出地
//虚类，定义虚析构函数，防止析构过程发生的内存泄漏
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender() = default;
    void virtual Log(Level level,LogEvent::ptr evtent) = 0;
    void setFormatter (LogFromatter::ptr format){
        m_formatter = format; 
    };
    LogFromatter::ptr getFormatter() const {return m_formatter;};
protected:
    LogFromatter::ptr m_formatter;//日志格式器   
    Level m_level;//输出哪些日志
};


//日志器
class Logger{
public:

    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string & s);

    void Log(Level level,LogEvent::ptr evtent);

    void debug(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addappender(LogAppender::ptr appender);
    void delappender(LogAppender::ptr appender);

    const Level getlevel()const {return m_level;};
    void setlevel(Level level){m_level = level;};

    ~Logger() = default;
private:

    std::string m_name;

    Level m_level;//日志器的日志级别,只有满足了日志级别的日志才输出

    std::list<LogAppender::ptr> m_appenders;

};

class StdoutLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void Log(Level level,LogEvent::ptr evtent) override;
    virtual ~StdoutLogAppender(); 
    StdoutLogAppender() = default;
private:
};
class FileLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(std::string & filename);
    void Log(Level level,LogEvent::ptr evtent) override;
    bool reopen();
    virtual ~FileLogAppender();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};
}
#endif