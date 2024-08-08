#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "log.h"
#include "util.h"
#include "config.h"
#include "loggers.h"
int main() {
   INIT_LOGGERS_STDOUT();
   loggersp::global_Warn_logger->addfileappender("/root/code/sm_own/Log_dir/log01.txt");
   loggersp::global_Warn_logger->log_cout(sm::Level::FATAL,CREATE_LOG_EVENT("event02"));
   loggersp::global_Error_logger->log_cout(sm::Level::WARN,CREATE_LOG_EVENT("event02"));
   std::string ss = "*01";
   sm::Config::ptr config = std::make_shared<sm::Config>();
   config->lookup<int>(ss,1,ss);
   config->lookup<int>(ss,1,ss);
}