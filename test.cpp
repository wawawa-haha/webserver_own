#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "log.h"
#include "util.h"


int main() {
    auto x = CREATE_LOG_EVENT("event01");
    auto y = CREATE_LOG_EVENT("event02");
    auto z = CREATE_LOG_EVENT("event03");
    auto log = sm::Logger_warp();
    log.addstdappender();
    log.addfileappender("/root/code/sm_own/log.txt");
    log.set_logger_level(sm::Level::DEBUG);
    log.log_cout(sm::Level::DEBUG,x);
    log.log_cout(sm::Level::DEBUG,y);
    log.log_cout(sm::Level::DEBUG,z);
}