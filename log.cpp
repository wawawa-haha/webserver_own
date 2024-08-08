#include"log.h"
#include <map>
#include <ctime>
namespace sm{
/*auto Globallogger = std::make_shared<sm::Logger>(std::string("logger"));//全局的logger
void Log_level_cout(LogEvent::ptr event,Level level){
    Globallogger->log(level,ptr);
}
void Log_appender_add(LogAppender::ptr appender){
    Globallogger->addappender(appender);
}
LogEvent::LogEvent(const char * content,int line,const char* file):m_threadID(sm::getSystemThreadId()){
    m_line = line;
    m_file = file;
}*/
Logger::Logger(const std::string & name,const char * format):m_name(name),m_formatter(std::make_shared<LogFormatter>(format)){
}
void Logger::Log(Level level,LogEvent::ptr event){
    //std::cout<<"Log cout begin"<<std::endl;
    //std::cout<<m_appenders.size()<<std::endl;
    //当输入的level大于logger的level才输出
    if(level >= m_level){
        for(auto & x : m_appenders){
            x->setFormatter(m_formatter);
            x->Log(shared_from_this(),level,event);
            //std::cout<<"完成一次输出"<<std::endl;
        }
    }
}
void Logger::debug(LogEvent::ptr event){
    Log(Level::DEBUG,event);
}
void Logger::warn(LogEvent::ptr event){
    Log(Level::WARN,event);
}
void Logger::info(LogEvent::ptr event){
    Log(Level::INFO,event);
}
void Logger::error(LogEvent::ptr event){
    Log(Level::ERROR,event);
}
void Logger::fatal(LogEvent::ptr event){
    Log(Level::FATAL,event);
}
void Logger::addappender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}
void Logger::delappender(LogAppender::ptr appender){
    for(auto it = m_appenders.begin();
        it!=m_appenders.end();++it){
        if(*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}
LogEvent::LogEvent(const char* content,int line, const char * file):
m_content(content),m_line(line),m_file(file){
    m_threadID = getSystemThreadId();
}
//LogFromatter::LogFromatter(const std::string & pattern):m_pattern(pattern){}
//the core func in class formatter
class StringFormatItem : public LogFormatter::FormatItem {
public:
    StringFormatItem(const std::string& str)
        :m_string(str) {}
    void format(std::shared_ptr<Logger> logger,std::ostream& os,Level level, LogEvent::ptr event) override {
        os << m_string;
    }
    ~StringFormatItem(){}
private:
    std::string m_string;
};
class MessageFormatItem : public LogFormatter::FormatItem{
public:
    MessageFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os,Level level, LogEvent::ptr  event) override{
        os << event->getContent();
     }
    ~MessageFormatItem(){}
};

class LevelFormatItem : public LogFormatter::FormatItem{
public:
    LevelFormatItem( const std::string & str = ""){}
    void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr event) override{
        os << LevelUtil:: toString(level);
    }
    ~LevelFormatItem(){}
};

class ElapseFormatItem : public LogFormatter::FormatItem{
public:
    ElapseFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << event->getelapse();
     }
    ~ElapseFormatItem(){}
};

class NameFormatItem : public LogFormatter::FormatItem{
public:
     NameFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << logger->getName();
     }
     ~NameFormatItem(){}
};

class ThreadIdFormatItem : public LogFormatter::FormatItem{
public:
     ThreadIdFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << event->getthreadid();
     }
     ~ThreadIdFormatItem(){}
};

class ThreadNameFormatItem : public LogFormatter::FormatItem{
public:
    ThreadNameFormatItem(const std::string & str = ""){}
     //thread name
     ~ThreadNameFormatItem (){}
};
class DateTimeFormatItem : public LogFormatter::FormatItem{
public:
    DateTimeFormatItem(const std::string & s):m_formatter(s){
        
    }
    void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        // 存储格式化后的时间字符串
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), m_formatter.c_str(), &tm);
        os << std::string(buffer);
    }
    ~DateTimeFormatItem(){}
private:
    std::string m_formatter;
};


class FilenameFormatItem : public LogFormatter::FormatItem{
public:
    FilenameFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << event->getfile();
     }
     ~FilenameFormatItem(){}
};


class LineFormatItem : public LogFormatter::FormatItem{
public:
    LineFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << event->getline();
     }
     ~LineFormatItem(){}
};


class FiberIdFormatItem: public LogFormatter::FormatItem{
public:
    FiberIdFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << event->getfiberID();
     }
    ~FiberIdFormatItem(){}
};


class NewLineFormatItem : public LogFormatter::FormatItem{
public:
    NewLineFormatItem (const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << std::endl;
     }
     ~NewLineFormatItem(){}
};

class TabFormatItem : public LogFormatter::FormatItem{
public:
    TabFormatItem(const std::string & str = ""){}
     void format(std::shared_ptr<Logger> logger,std::ostream & os, Level level,LogEvent::ptr  event) override{
        os << "\t";
     }
    ~TabFormatItem(){}
};


void LogFormatter::init() {
    //str, format, type
    std::vector<std::tuple<std::string, std::string, int> > vec;

    std::string nstr;

    for(size_t i = 0; i < m_pattern.size(); ++i) {

        if(m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }

        if((i + 1) < m_pattern.size()) {
            if(m_pattern[i + 1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while(n < m_pattern.size()) {
            if(!fmt_status && (!isalpha(m_pattern[n]) && m_pattern[n] != '{'
                    && m_pattern[n] != '}')) {
                str = m_pattern.substr(i + 1, n - i - 1);
                break;
            }
            if(fmt_status == 0) {
                if(m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i - 1);
                    //std::cout << "*" << str << std::endl;
                    fmt_status = 1; //解析格式
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            } else if(fmt_status == 1) {
                if(m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    //std::cout << "#" << fmt << std::endl;
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }
            ++n;
            if(n == m_pattern.size()) {
                if(str.empty()) {
                    str = m_pattern.substr(i + 1);
                }
            }
        }

        if(fmt_status == 0) {
            if(!nstr.empty()) {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));//single char ex: %a,%b ...
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n - 1;
        } else if(fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
            m_error = true;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    }

    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
    static std::map<std::string, std::function<LogFormatter::FormatItem::ptr(const std::string& str)> > s_format_items = {
//#define XX(str, C) \
//        {#str, [](const std::string& fmt) { return LogFormatter::FormatItem::ptr(new C(fmt));}}
#define XX(str, C) \
    {#str, [](const std::string& fmt) -> LogFormatter::FormatItem::ptr { return std::make_shared<C>(fmt); }}//返回相应的LogFormatter::FormatItem::ptr

        XX(m, MessageFormatItem),           //m:消息
        XX(p, LevelFormatItem),             //p:日志级
        XX(r, ElapseFormatItem),            //r:累计毫秒数
        XX(c, NameFormatItem),              //c:日志名称
        XX(t, ThreadIdFormatItem),          //t:线程id
        XX(n, NewLineFormatItem),           //n:换行
        XX(d, DateTimeFormatItem),          //d:时间
        XX(f, FilenameFormatItem),          //f:文件名
        XX(l, LineFormatItem),              //l:行号
        XX(T, TabFormatItem),               //T:Tab
        XX(F, FiberIdFormatItem),           //F:协程id
        XX(N, ThreadNameFormatItem),        //N:线程名称
#undef XX
    };


    for(auto& i : vec) {
        //for this tuple vec，first or second or false info was pubshed back
        if(std::get<2>(i) == 0) {
            m_formatitems.push_back(LogFormatter::FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if(it == s_format_items.end()) {
                m_formatitems.push_back(LogFormatter::FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
                m_error = true;
            } else {
                m_formatitems.push_back(it->second(std::get<1>(i)));
            }
        }

        //std::cout << "(" << std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" << std::endl;
    }
    //std::cout << m_items.size() << std::endl;
}
//use formatteritem - format func to cout 
//std::string format(std::shared_ptr<Logger> logger,Level level,LogEvent::ptr event);
std::string LogFormatter::format(std::shared_ptr<Logger> logger,Level level,LogEvent::ptr event){
    std::stringstream ss;
    for(auto x: m_formatitems){
        //format(std::shared_ptr<Logger> logger,std::ostream & s, Level level, LogEvent::ptr  event);
        x->format(logger,ss,level,event);
    }
    return ss.str();
}

LogFormatter::FormatItem::~FormatItem() {
    // Provide implementation for virtual destructor
}
void LogFormatter::FormatItem::format(std::shared_ptr<Logger> logger, std::ostream& s, Level level, LogEvent::ptr event) {
    // Provide a default implementation or leave it abstract if it's a pure virtual function
}


void StdoutLogAppender::Log(std::shared_ptr<Logger> logger, Level level, LogEvent::ptr event)  {
            std::cout << m_formatter->format(logger, level, event) << std::endl;
}

void FileLogAppender::Log(std::shared_ptr<Logger> logger, Level level, LogEvent::ptr event)  {
    m_filestream << m_formatter->format(logger,level,event); 
}

void FileLogAppender::open(){
    m_filestream.open(m_filename);
}
FileLogAppender::FileLogAppender(const char * filename):m_filename(filename){
    open();
}

StdoutLogAppender::StdoutLogAppender(){}

StdoutLogAppender::~StdoutLogAppender(){}

FileLogAppender::~FileLogAppender(){m_filestream.close();}

Logger_warp::Logger_warp(const char * name,const char * format,Level level){
    //std::cout<<"xxxxxxx"<<std::endl;
    m_logger = std::make_shared<sm::Logger>(name,format);
    m_logger->setlevel(level);
}
    void Logger_warp::addstdappender(){
        //std::cout<<"添加stdappender"<<std::endl;
        m_logger->addappender(std::make_shared<sm::StdoutLogAppender>());
    }
    void Logger_warp::addfileappender(const char * s){
        //std::cout<<"添加fileappender"<<std::endl;
        m_logger->addappender(std::make_shared<sm::FileLogAppender>(s));
    }
    void Logger_warp::log_cout(Level level,LogEvent::ptr event){
        //std::cout<<"logcout运行"<<std::endl;
        m_logger->Log(level,event);
    }

}


