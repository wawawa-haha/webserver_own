
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "conf.h"
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

    YAML::Node root = YAML::LoadFile("/root/code/sm_own/conf.yaml");
    Config::LoadFromYaml(root);
    //Config::tarvel();
    return 0;
}
