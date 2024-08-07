#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "log.h"
#include "util.h"


int main() {
    auto log1 = sm::Logger_warp("logger_WARN");
    auto log2 = sm::Logger_warp("logger_ERROR");
    
    log1.addstdappender();
    log1.addfileappender("/root/code/sm_own/log.txt");

    log2.addstdappender();
    log2.addfileappender("/root/code/sm_own/log.txt");
    
    log1.set_logger_level(sm::Level:: WARN);
    log2.set_logger_level(sm::Level:: ERROR);
    log1.log_cout(sm::Level::DEBUG,CREATE_LOG_EVENT("event01"));
    log1.log_cout(sm::Level::FATAL,CREATE_LOG_EVENT("event02"));
    log1.log_cout(sm::Level::WARN,CREATE_LOG_EVENT("event02"));
    log2.log_cout(sm::Level::DEBUG,CREATE_LOG_EVENT("event01"));
    log2.log_cout(sm::Level::FATAL,CREATE_LOG_EVENT("event02"));
    log2.log_cout(sm::Level::WARN,CREATE_LOG_EVENT("event02"));
}