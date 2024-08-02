#ifndef _SM_CONF
#define _SM_CONF

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <map>
#include <yaml-cpp/yaml.h>
// 定义好的基类
class ConfVarBase {
public:
    typedef std::shared_ptr<ConfVarBase> ptr;

    ConfVarBase( std::string &name,  std::string &description )
        : m_name(name), m_description(description) {
           std::transform(name.begin(), name.end(), name.begin(),
               [](unsigned char c) { return std::tolower(c); });
        }

    virtual ~ConfVarBase() {}

    const std::string &getName() const { return m_name; }

    const std::string &getDesc() const { return m_description; }

    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string &val) = 0;

protected:
    std::string m_name;
    std::string m_description;
};

template <class T>
class ConfVar : public ConfVarBase {
public:
    typedef std::shared_ptr<ConfVar> ptr;

    ConfVar( std::string &name,  std::string &description = "", const T &val = T())
        : ConfVarBase(name, description), m_val(val) {}

    std::string toString() const override {
        try {
            return boost::lexical_cast<std::string>(m_val);
        } catch (const std::exception &e) {
            std::cout << e.what() << " ConfVar 配置val异常" << std::endl;
        }
        return "";
    }

    bool fromString(const std::string &val) override {
        try {
            m_val = boost::lexical_cast<T>(val);
            return true;
        } catch (const std::exception &e) {
            std::cout << e.what() << " ConfVar form string to val异常" << std::endl;
        }
        return false;
    }

private:
    T m_val;
};

class Config {
    
public:
    typedef std::map<std::string, ConfVarBase::ptr> confvarmap;

    template<typename T>
    static typename ConfVar<T>::ptr lookup(const std::string &s) {
        auto i = Config::m_confmap.find(s);
        if (i == Config::m_confmap.end()) {
            return nullptr;
        } else {
            // m_confmap 对应的值是 ConfVarBase::ptr，所以需要进行类型转换
            return std::dynamic_pointer_cast<ConfVar<T> >(i->second);
        }
    }

    template<typename T>
    static typename ConfVar<T>::ptr lookup(const std::string &name, const std::string &desc , const T &val = T()) {
        auto tmp = lookup<T>(name);
        if (tmp) {
            // 后续用日志系统输出
            std::cout << "已经存在" << std::endl;
            return tmp;
        }
        if (name.find_first_not_of("QWERTYUIOPASDFGHJKLZXCVBNM0123456789._qwertyuiopasdfghjklzxcvbnm") != std::string::npos) {
            // 日志系统输出
            std::cout << "输出不合法" << std::endl;
            throw std::invalid_argument(name);
        }
        typename ConfVar<T>::ptr v(new ConfVar<T>(name, desc, val));
        Config::m_confmap[name] = v;
        return v;
    }

    static void tarvel() {
        for (const auto &x : Config::m_confmap) {
            std::cout<< x.first << "--------" << x.second->toString() << std::endl;
        }
    }
    static void LoadFromYaml(const YAML::Node & root);

static void ListAllMember( std::string& prefix,
                          const YAML::Node& node,
                          std::list<std::pair<std::string, const YAML::Node> > & output) ;

    ConfVarBase::ptr static LookUpBase(const std::string & name);

private:
    static confvarmap m_confmap; 
};

// 静态变量的定义


#endif // _SM_CONF


//git remote add origin git@github.com/wawawa-haha/webserver_own.git
