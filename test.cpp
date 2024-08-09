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
   sm::Config::lookup<int>("port",8080,"the port number");
   sm::Config::lookup<std::string>("logs[0].name","tem","logger 01 name");
   //loggersp::global_Info_logger->addstdappender();
   //loggersp::global_Info_logger->addfileappender("/root/code/sm_own/Log_dir/log_01.txt");
   YAML::Node root = test_yaml("/root/code/sm_own/conf/conf.yaml");
   sm::Config::LoadFormYaml(root);
   std::cout<<sm::Config::getconfsize()<<std::endl;
   /*loggersp::global_Warn_logger->addfileappender("/root/code/sm_own/Log_dir/log01.txt");
   loggersp::global_Warn_logger->addstdappender();
   loggersp::global_Warn_logger->log_cout(sm::Level::FATAL,CREATE_LOG_EVENT("event02"));
   loggersp::global_Error_logger->log_cout(sm::Level::WARN,CREATE_LOG_EVENT("event02"));*/
   auto tem = sm::Config::lookup<int>("port");
   std::cout<<tem->toString()<<std::endl;

   auto tem2 = sm::Config::lookup<std::string>("logs[0].name");
   //std::cout<<tem2;
   std::cout<<tem2->toString()<<std::endl;

   //YAML::Node tem = test_yaml("/root/code/sm_own/conf/conf.yaml");
   //sm::Config::LoadFormYaml(tem);
   //std::cout<<sm::Config::getconfsize()<<std::endl;
}