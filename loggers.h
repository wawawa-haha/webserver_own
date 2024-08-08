// loggers.h
#ifndef LOGGERS_H
#define LOGGERS_H

#include <memory>
#include "log.h"

namespace loggersp {
    extern sm::Logger_warp::ptr global_Debug_logger;
    extern sm::Logger_warp::ptr global_Info_logger;
    extern sm::Logger_warp::ptr global_Warn_logger;
    extern sm::Logger_warp::ptr global_Error_logger;
    extern sm::Logger_warp::ptr global_Fatal_logger;
}

#endif // LOGGERS_H