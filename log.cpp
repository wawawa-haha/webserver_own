#include"log.h"
namespace sm{
Logger::Logger(const std::string & name):m_name(name){
}
void Logger::Log(Level level,LogEvent::ptr event){
    //当输入的level大于logger的level才输出
    if(level >= m_level){
        for(auto & x : m_appenders){
            x->Log(level,event);
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
std::string LogFromatter::format(LogEvent::ptr event){
    std::string res = "";
    res+="m_line:";
    res+=std::to_string(event->m_line);
    res+=" ";
    res+="m_threadID:";
    res+=std::to_string(event->m_threadID);
    return res;
}
void StdoutLogAppender::Log(Level level,LogEvent::ptr event){
    if(level>=m_level){
        std::cout << m_formatter->format(event) << std::endl ;
    }
}
FileLogAppender::FileLogAppender(std::string & filename):m_filename(filename){
}
void FileLogAppender::Log(Level level,LogEvent::ptr event){
    reopen();
    m_filestream << m_formatter->format(event);
}
bool FileLogAppender::reopen(){
    if(m_filestream){
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !!m_filestream;
}
FileLogAppender::~FileLogAppender(){}
StdoutLogAppender::~StdoutLogAppender(){}
}
