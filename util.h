#ifndef __SM_UTIL
#define __SM_UTIL
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
namespace sm{
pid_t getSystemThreadId(); 
}
#endif
