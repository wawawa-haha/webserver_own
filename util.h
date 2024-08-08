#ifndef __SM_UTIL
#define __SM_UTIL
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <yaml-cpp/yaml.h>
#include "log.h"
namespace sm{
pid_t getSystemThreadId(); 
//void printyaml(const YAML::Node& node ,int level);
}
#endif
