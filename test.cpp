#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "loggers.h"
#include "log.h"
#include "config.h"

YAML::Node test_yaml(char const * filename){
   YAML::Node root = YAML::LoadFile(filename);
   return root;
}
void printyaml(const YAML::Node& node ,int level){
   std::cout<<"*******"<<std::endl;
   if(node.IsScalar()){
      std::stringstream ss;
      ss  << std::string(level*4,' ')<<node.Scalar() << '-' << node.Type() << '-' <<level;
      loggersp::global_Info_logger->log_cout(sm::Level::INFO,CREATE_LOG_EVENT(ss.str().c_str()));
      
   }else if(node.IsNull()){
      std::stringstream ss;
      ss  <<std::string(level*4,' ')<< "NULL"<< '-' << node.Type() << '-' <<level;
      loggersp::global_Info_logger->log_cout(sm::Level::INFO,CREATE_LOG_EVENT(ss.str().c_str()));
   }else if(node.IsMap()){
      for(auto i = node.begin();i!=node.end();i++){
          std::stringstream ss;
         ss  <<std::string(level*4,' ')<< i->first << '-' << i->second.Type() << '-' <<level;
         loggersp::global_Info_logger->log_cout(sm::Level::INFO,CREATE_LOG_EVENT(ss.str().c_str()));
         printyaml(i->second ,level+1);
      }
   }else if(node.IsSequence()){
      for(int i = 0;i<node.size();i++){
         std::stringstream ss;
         ss   <<std::string(level*4,' ')<< node[i].Type() << '-' <<level;
         loggersp::global_Info_logger->log_cout(sm::Level::INFO,CREATE_LOG_EVENT(ss.str().c_str()));
         printyaml(node[i] ,level+1);
      }

   }
}
int main() {
   
   loggersp::global_Info_logger->addfileappender("/root/code/sm_own/Log_dir/log_01.txt");
   YAML::Node tem = test_yaml("/root/code/sm_own/conf/conf.yaml");
   std::list<std::pair<std::string , const YAML::Node> >temlist;
   std::string s = "";
   sm::flatten_Yaml(s,tem,temlist);
   for(auto x:temlist){
      std::cout<<x.first<<std::endl;
   }
   //printyaml(tem,0);
   return 0;
   /*loggersp::global_Warn_logger->addfileappender("/root/code/sm_own/Log_dir/log01.txt");
   loggersp::global_Warn_logger->addstdappender();
   loggersp::global_Warn_logger->log_cout(sm::Level::FATAL,CREATE_LOG_EVENT("event02"));
   loggersp::global_Error_logger->log_cout(sm::Level::WARN,CREATE_LOG_EVENT("event02"));*/
}