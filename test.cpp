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
   sm::Config::lookup("port",(int)8080,"the port number");
   sm::Config::lookup("floatxx",(float)123.456,"logger 01 name");
   sm::Config::lookup("vec",(std::vector<int>){0},"logger 02 name");
   sm::Config::lookup("list",(std::list<int>){0},"logger 03 name");
   sm::Config::lookup("set",(std::set<int>){0},"logger 04 name");
   sm::Config::lookup("uset",(std::unordered_set<int>){0},"logger 05 name");
   sm::Config::lookup("umap",(std::unordered_map<std::string,int>){{"A",0}},"logger 06 name");
   sm::Config::lookup("map",(std::map<std::string,int>){{"A",0}},"logger 07 name");
   loggersp::global_Info_logger->addstdappender();
   loggersp::global_Info_logger->addfileappender("/root/code/sm_own/Log_dir/log_01.txt");
   YAML::Node root = test_yaml("/root/code/sm_own/conf/conf.yaml");
   sm::Config::LoadFormYaml(root);
   printyaml(root ,0);
   /*loggersp::global_Warn_logger->addfileappender("/root/code/sm_own/Log_dir/log01.txt");
   loggersp::global_Warn_logger->addstdappender();
   loggersp::global_Warn_logger->log_cout(sm::Level::FATAL,CREATE_LOG_EVENT("event02"));
   loggersp::global_Error_logger->log_cout(sm::Level::WARN,CREATE_LOG_EVENT("event02"));*/
   auto tem = sm::Config::lookup<int>("port");//一个
   std::cout<<tem->toString()<<std::endl;

   auto tem2 = sm::Config::lookup<float>("floatxx");
   std::cout<<tem2->toString()<<std::endl;

   auto tem3 = sm::Config::lookup<std::vector<int> >("vec");
   std::cout<<tem3->toString()<<std::endl;

   auto tem4 = sm::Config::lookup<std::list<int> >("list");
   std::cout<<tem4->toString()<<std::endl;
   
   auto tem5 = sm::Config::lookup<std::set<int> >("set");
   std::cout<<tem5->toString()<<std::endl;

   auto tem6 = sm::Config::lookup<std::unordered_set<int> >("uset");
   std::cout<<tem6->toString()<<std::endl;

   auto tem7 = sm::Config::lookup<std::unordered_map<std::string,int> >("umap");
   std::cout<<tem7->toString()<<std::endl;

    auto tem8 = sm::Config::lookup<std::map<std::string,int> >("map");
   std::cout<<tem8->toString()<<std::endl;

   //YAML::Node tem = test_yaml("/root/code/sm_own/conf/conf.yaml");
   //sm::Config::LoadFormYaml(tem);
   //std::cout<<sm::Config::getconfsize()<<std::endl;

}