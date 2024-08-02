#include <conf.h>

Config::confvarmap Config::m_confmap;

ConfVarBase::ptr  Config::LookUpBase(const std::string & name){
    auto it = Config::m_confmap.find(name);
    if(it != m_confmap.end()){
        return it->second;
    }else{
        return nullptr;
    }
}

//该函数按照配置的等级将每一项加入到list中
void Config::ListAllMember( std::string& prefix,
                          const YAML::Node& node,
                          std::list<std::pair<std::string, const YAML::Node>>& output) {
    // 检查前缀是否合法
    if(prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789[]")
            != std::string::npos) {
        std::cout << "Config invalid name: " << prefix << std::endl;
        return;
    }

    // 如果前缀不为空，加入到输出列表中
    if (!prefix.empty()) {
        output.push_back(std::make_pair(prefix, node));
    }

    // 处理映射类型节点
    if(node.IsMap()) {
        for(auto it = node.begin(); it != node.end(); ++it) {
            std::string new_prefix = prefix.empty() ? it->first.Scalar()
                                                    : prefix + "." + it->first.Scalar();
            ListAllMember(new_prefix, it->second, output);
        }
    }
    // 处理序列类型节点
    else if (node.IsSequence()) {
        size_t index = 0;
        for (const auto& item : node) {
            std::string new_prefix = prefix.empty() ? std::to_string(index) 
                                                    : prefix + "." + std::to_string(index) ;
            ListAllMember(new_prefix, item, output);
            ++index;
        }
    }
}

void Config::LoadFromYaml(const YAML::Node& root) {

    std::list<std::pair<std::string, const YAML::Node>> all_nodes; // all_nodes 每一个都是 pair，一个 string 对应一个 node
    std::string str = "";

    ListAllMember(str, root, all_nodes);

    for(auto x:all_nodes){
        std::cout<<x.first<<"******"<<x.second<<std::endl;
    }


    for (auto& node_pair : all_nodes) {

        std::string key = node_pair.first;

        if (key.empty()) continue;
        
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        // 根据配置项的键和值插入到 m_confmap

        if (node_pair.second.IsScalar()) {
            // 假设所有配置项都是 std::string 类型，实际应用中需要根据实际情况选择类型

            auto var = std::make_shared<ConfVar<std::string> >(key, str, node_pair.second.Scalar());
            m_confmap[key] = var;

        } else {
            // 处理非标量类型（如映射或序列）
            std::stringstream ss;
            ss << node_pair.second;
            auto var = std::make_shared<ConfVar<std::string> >(key, str, ss.str());
            m_confmap[key] = var;
            ss.clear();
        }
    }
}

/*void Config::LoadFormYaml(const YAML::Node& root) {
    
    std::list<std::pair<std::string, const YAML::Node>> all_nodes;//all_nodes每一个都是pair，一个string对应一个node&
    std::string str = "";
    ListAllMember(str, root, all_nodes);

    for (auto& node_pair : all_nodes) {

        std::string key = node_pair.first;

        if (key.empty()) continue;

        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        ConfVarBase::ptr var = LookUpBase(key);
        
        if (var == nullptr ) {
            m_confmap[key] = var;
            if (node_pair.second.IsScalar()) {

                var->fromString(node_pair.second.Scalar());

            } else {
                std::stringstream ss;
                ss << node_pair.second;
                var->fromString(ss.str());
            }
        }
    }
}
*/