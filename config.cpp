#include <config.h>
namespace sm{
Config::confmap Config::s_confmap;
void flatten_Yaml(const std::string& prefix,
                  const YAML::Node& node,
                  std::list<std::pair<std::string, const YAML::Node>>& output) {
    if (prefix.find_first_not_of("qwertyuiopasdfghjklzxcvbnm.0123456789[]") != std::string::npos) {
        std::stringstream ss;
        ss << "invalid yaml prefix: " << prefix;
        loggersp::global_Error_logger->log_cout(sm::Level::ERROR, CREATE_LOG_EVENT(ss.str().c_str()));
        return;
    }

    output.push_back(std::make_pair(prefix, node));

    if (node.IsMap()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            std::string new_prefix = prefix.empty() ? it->first.as<std::string>() : prefix + "." + it->first.as<std::string>();
            flatten_Yaml(new_prefix, it->second, output);
        }
    } else if (node.IsSequence()) {
        for (size_t i = 0; i < node.size(); ++i) {
            std::string new_prefix = prefix + "[" + std::to_string(i) + "]";
            flatten_Yaml(new_prefix, node[i], output);
        }
    }
}
ConfigVarBase::ptr Config::LookupBase(std::string &name){
    auto it = s_confmap.find(name);
    return it == s_confmap.end() ? nullptr : it->second;
}
void Config::LoadFormYaml(const YAML::Node& root){
    std::list<std::pair<std::string , const YAML::Node> > temlist;
    flatten_Yaml("",root,temlist);
    for(auto i :temlist){
        auto key = i.first;
        if(key.empty()||key[key.size()-1] == ']'){
            continue;
        }
        auto congbaseptr = LookupBase(key);
        if(congbaseptr){
            if(i.second.IsScalar()){
                congbaseptr->fromString(i.second.Scalar());
            }else{
                std::stringstream ss;
                ss << i.second;
                congbaseptr->fromString(ss.str());
            }
        }
    } 
}
/*static void Config::LoadFromYaml(const YAML::Node& root){
    std::list<std::pair<std::string , const YAML::Node> flatten_yaml_list;
    std::string perfix = "";
    flatten_Yaml(perfix,root,flatten_yaml_list);
}*/
}