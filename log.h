#ifndef _LOG_H
#define _LOG_H
#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include "util.h"

#define CREATE_LOG_EVENT(content) std::make_shared<sm::LogEvent>(content, __LINE__, __FILE__)
//#define CREATE_LOG_STD_APPENDER() std::make_shared<sm::StdoutLogAppender>()
//#define CREATE_LOG_FILE_APPENDER(s) std::make_shared<sm::FileLogAppender>(s)

namespace sm{

class Logger;
//每个日志出现，当作一个Logevent
enum class Level{

        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4
};
class LevelUtil {
public:
    static std::string toString(Level level) {
        switch (level) {
            case Level::DEBUG: return "DEBUG";
            case Level::INFO: return "INFO";
            case Level::WARN: return "WARN";
            case Level::ERROR: return "ERROR";
            case Level::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    static Level fromString(const std::string& str) {
        if (str == "DEBUG") return Level::DEBUG;
        if (str == "INFO") return Level::INFO;
        if (str == "WARN") return Level::WARN;
        if (str == "ERROR") return Level::ERROR;
        if (str == "FATAL") return Level::FATAL;
        throw std::invalid_argument("Unknown level string");
    }
};
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(const char* content,int line, const char * file);
    const char* getfile() const {return m_file;}
    int32_t getline() const {return m_line;}
    uint32_t getelapse() const {return elapse;}
    pid_t getthreadid() const {return m_threadID;}
    uint32_t getfiberID() const {return m_fiberID;}
    std::string getContent() const {return m_content;}
    uint64_t gettime()const{return m_time;}
public:
    //与构造函数使用初始化成员列表一样
    const char* m_file = nullptr;
    int m_line;
    uint32_t elapse = 0;
    pid_t m_threadID = 0;
    uint32_t m_fiberID = 0;
    uint64_t m_time;
    const char* m_content ;
};

//日志格式器
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(std::shared_ptr<Logger> logger,Level level,LogEvent::ptr event);
    LogFormatter (const std::string & pattern):m_pattern(pattern){init();}
    
    class FormatItem{
        public:
            typedef std::shared_ptr<FormatItem> ptr;
            FormatItem(){}
            virtual ~FormatItem();
            virtual void format(std::shared_ptr<Logger> logger,std::ostream & s, Level level, LogEvent::ptr  event);
    };
    void init();//init the pattern  patternitem vec by the pattern string
private:
    bool m_error = true;
    std::shared_ptr<Logger> logger;
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_formatitems;
};

//日志输出地
//虚类，定义虚析构函数，防止析构过程发生的内存泄漏
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender(){}
    virtual ~LogAppender(){};
    virtual void Log(std::shared_ptr<Logger> logger, Level level, LogEvent::ptr event){};
    void setFormatter (LogFormatter::ptr format){
        m_formatter = format; 
    };
    LogFormatter::ptr getFormatter() const {return m_formatter;};
protected:
    LogFormatter::ptr m_formatter;//日志格式器   
    Level m_level;//输出哪些日志
};


//日志器
class Logger : public std::enable_shared_from_this<Logger>{
public:

    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string & s,const char * format = "%d{%Y-%m-%d %H:%M:%S}%T%c%T[%p]%T%t%T%F%T<%f%l>%T%m%n");

    void Log(Level level,LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addappender(LogAppender::ptr appender);
    void delappender(LogAppender::ptr appender);

    const Level getlevel()const {return m_level;};
    void setlevel(Level level){m_level = level;};

    const std::string& getName(){return m_name;}
    int get_appendersize(){return m_appenders.size();}
    ~Logger() = default;
private:
    std::string m_name;
    Level m_level;//日志器的日志级别,只有满足了日志级别的日志才输出
    LogFormatter::ptr m_formatter;
    std::list<LogAppender::ptr> m_appenders;//对于每个appender有相应的formatter
};

class StdoutLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    virtual void Log(std::shared_ptr<Logger> logger, Level level, LogEvent::ptr event) override;
    virtual ~StdoutLogAppender(); 
    StdoutLogAppender();
private:
};

class FileLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    
    FileLogAppender(const char * filename);
    virtual void Log(std::shared_ptr<Logger> logger, Level level, LogEvent::ptr event) override;
    void open();
    virtual ~FileLogAppender();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};
class Logger_warp{
public:
    typedef std::shared_ptr<Logger_warp> ptr;
    Logger_warp(const char * name,const char * format,Level level);
    void addstdappender();
    void addfileappender(const char * s);
    void log_cout(Level level,LogEvent::ptr event);
    Logger::ptr get_logger(){return m_logger;}
    Logger::ptr m_logger;
};
}


#endif

