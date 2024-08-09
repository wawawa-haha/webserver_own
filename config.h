#ifndef _CONF_H_
#define _CONF_H_
#include <memory>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <map>
#include <yaml-cpp/yaml.h>
#include <list>
#include <algorithm>
#include "loggers.h"
#include "log.h"


namespace sm{
class ConfigVarBase{
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string & name,const std::string & desc="")
        :m_name(name),m_desc(desc){
            //std::transform(std::transform(name.begin(), name.end(), [](unsigned char c) { return std::tolower(c); }));
        }
    virtual ~ConfigVarBase(){}
    const std::string& getName() const {return m_name;}
    const std::string& getDesc() const {return m_desc;}
    virtual std::string toString() = 0;
    virtual bool fromString(const std::string & val) = 0;
protected:
    std::string m_name;
    std::string m_desc;
};

template<class F,class T>
class lexiCast{
public:
    T operator()(const F& val){
        return boost::lexical_cast<T>(val);
    }
};


template<class T>
class lexiCast<std::string,std::vector<T> >{
public:
    std::vector<T> operator()(const std::string& val){
        std::cout<<"******"<<std::endl;
        typename std::vector<T> v;
        YAML::Node node = YAML::Load(val);
        std::stringstream ss;
        for(int i = 0;i<node.size();i++){
            ss.str("");
            ss<< node[i];
            v.push_back(lexiCast<std::string,T>()(ss.str()));
        }
        return v;
    }
};

template<class T>
class lexiCast<std::vector<T>,std::string>{
public:
    std::string operator()(std::vector<T>& val){
        std::stringstream ss;
        for(int i = 0; i < val.size();i++){
            if(i == 0){
                ss<<val[i];
            }else{
                ss<<','<<val[i];
            }
        }
        return ss.str();
    }
};




template<class T,class FromString = lexiCast<std::string,T>,class ToString = lexiCast<T,std::string> >
class ConfigVar : public ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVar<T> > ptr; 
    ConfigVar(std::string name,
              const T& val,
              std::string desc):
    ConfigVarBase(name,desc),
    m_val(val)
    {}
    ~ConfigVar(){}
    std::string toString() override{
        try{
            //std::cout<<"tostring begin"<<std::endl;
            return ToString()(m_val);
            //return boost::lexical_cast<std::string>(m_val);
        }catch(std::exception& e){
            loggersp::global_Error_logger->log_cout(sm::Level::ERROR,CREATE_LOG_EVENT("can not tran from configvar_val to string"));
        }
    }

    bool fromString(const std::string & val) override{
        try{
            std::cout<<"开始fromstring"<<std::endl;
            m_val = FromString()(val);
           // m_val = boost::lexical_cast<T>(val);
            return true;
        }catch(std::exception& e){
            loggersp::global_Error_logger->log_cout(sm::Level::ERROR,CREATE_LOG_EVENT("can not tran from string to configvar_val"));
        }
        return false;
    }

private:
    T m_val;
};

class Config{
public:
    typedef std::shared_ptr<Config> ptr;
    typedef std::map<std::string,ConfigVarBase::ptr> confmap;
    
    Config(){}

    //创建用lookup

    template<class T> 
    static typename ConfigVar<T>::ptr lookup(const std::string& name,
                                            const T& val,
                                            const std::string& desc)
    {
        //std::cout <<"looup begin " << val << std::endl;
        auto tmp = lookup<T>(name);
        if(tmp == nullptr){
            if(name.find_first_not_of("qwertyuiopasdfghjklzxcvbnm.1234567890[]")!=std::string::npos){
                 loggersp::global_Error_logger->log_cout(sm::Level::ERROR,CREATE_LOG_EVENT("config name is invalid"));
                 throw std::invalid_argument(name);
            }
            auto confval = std::make_shared<ConfigVar<T>>(name,val,desc);
            s_confmap[name] = confval;
        }else{
            loggersp::global_Info_logger->log_cout(sm::Level::INFO,CREATE_LOG_EVENT("in config map ,name-configvar_base has exit "));
            return tmp;
        }
    }

    //调用时必须显式给出T的类型
    template<class T> 
    static typename ConfigVar<T>::ptr lookup(const std::string& name){
        auto it  = s_confmap.find(name);
        if(it == s_confmap.end()){
            return nullptr;
        }
        return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);//找到的是configbarbase::ptr
    }

    static void LoadFormYaml(const YAML::Node& root);

    static ConfigVarBase::ptr LookupBase(std::string &name);

    static int getconfsize(){return s_confmap.size();}
private:
    static confmap s_confmap;
};

void flatten_Yaml(const std::string& perfix ,
                const YAML::Node& node,
                std::list<std::pair<std::string , const YAML::Node> >& output 
);
}
#endif