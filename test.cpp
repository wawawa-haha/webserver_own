
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "log.h"
/*void print_yaml(const YAML::Node& node, int level) {
    std::string indent(level * 2, ' '); // 根据level生成缩进空格

    if (node.IsScalar()) {
        std::cout << indent << "- " << node.Scalar() << " (" << node.Tag() << ")\n";
    } else if (node.IsNull()) {
        std::cout << indent << "NULL (" << node.Tag() << ")\n";
    } else if (node.IsMap()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            std::cout << indent << "- " << it->first.as<std::string>() << ":\n";
            print_yaml(it->second, level + 1);
        }
    } else if (node.IsSequence()) {
        size_t index = 0;
        for (const auto& item : node) {
            std::cout << indent << "- " << index++ << ":\n";
            print_yaml(item, level + 1);
        }
    }
}*/


int main() {
    //使用的时候首先初始化Logger，然后初始化LogAppender，然后初始化LogAppender的LogFormatter，然后调用Logger的Log方法即可
    auto x = std::make_shared<sm::LogEvent>();
    x->m_file = "文件名";
    x->m_line = 666;
    x->elapse = 123;
    x->m_threadID = 234;
    x->m_fiberID = 345;
    x->m_time = 456;
     /*m:消息
        XX(p, LevelFormatItem),             //p:日志级别
        XX(r, ElapseFormatItem),            //r:累计毫秒数
        XX(c, NameFormatItem),              //c:日志名称
        XX(t, ThreadIdFormatItem),          //t:线程id
        XX(n, NewLineFormatItem),           //n:换行
        XX(d, DateTimeFormatItem),          //d:时间
        XX(f, FilenameFormatItem),          //f:文件名
        XX(l, LineFormatItem),              //l:行号
        XX(T, TabFormatItem),               //T:Tab
        XX(F, FiberIdFormatItem),           //F:协程id
        XX(N, ThreadNameFormatItem),        //N:线程名称*/
    std::string tem = "event_con";
    x->m_content = tem;

    std::string file_name =  "/root/code/sm_own/log.txt";

    auto stdappender =  std::make_shared<sm::FileLogAppender>(file_name);

    auto logger = std::make_shared<sm::Logger>(std::string("logger_name"));

    auto formatter = std::make_shared<sm::LogFormatter>("%p%T%r%T%t%T%f%T%F::::------");

    stdappender->setFormatter(formatter);

    logger->addappender(stdappender);

    logger->setlevel(sm::Level::DEBUG);

    logger->Log(sm::Level::DEBUG,x);

return 0;
}
