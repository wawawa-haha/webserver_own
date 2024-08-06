
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
    auto stdappender =  std::make_shared<sm::StdoutLogAppender>();
    auto logger = std::make_shared<sm::Logger>(std::string("ascasc"));
    auto formatter = std::make_shared<sm::LogFromatter>();
    stdappender->setFormatter(formatter);
    logger->addappender(stdappender);
    logger->setlevel(sm::Level::DEBUG);
    logger->Log(sm::Level::DEBUG,x);
return 0;
}
