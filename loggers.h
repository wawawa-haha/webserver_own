#ifndef LOGGERS_H
#define LOGGERS_H

#include <memory>
#include "log.h"  // 假设这是 Logger_warp 的定义头文件
#define INIT_LOGGERS_STDOUT()     {loggersp::global_Debug_logger->addstdappender(); \ 
    loggersp::global_Info_logger->addstdappender();  \
    loggersp::global_Warn_logger->addstdappender();  \
    loggersp::global_Error_logger->addstdappender(); \
    loggersp::global_Fatal_logger->addstdappender();}  

namespace loggersp {
    extern sm::Logger_warp::ptr global_Debug_logger;
    extern sm::Logger_warp::ptr global_Info_logger;
    extern sm::Logger_warp::ptr global_Warn_logger;
    extern sm::Logger_warp::ptr global_Error_logger;
    extern sm::Logger_warp::ptr global_Fatal_logger;
}

#endif // LOGGERS_H
