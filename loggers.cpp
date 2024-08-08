// loggers.cpp
#include "loggers.h"

namespace loggersp {
    auto default_format = "%d{%Y-%m-%d %H:%M:%S}%T%c%T[%p]%T%t%T%F%T<%f%l>%T%m%n";

    sm::Logger_warp::ptr global_Debug_logger = std::make_shared<sm::Logger_warp>("global_Debug_logger", default_format, sm::Level::DEBUG);
    sm::Logger_warp::ptr global_Info_logger = std::make_shared<sm::Logger_warp>("global_Info_logger", default_format, sm::Level::INFO);
    sm::Logger_warp::ptr global_Warn_logger = std::make_shared<sm::Logger_warp>("global_Warn_logger", default_format, sm::Level::WARN);
    sm::Logger_warp::ptr global_Error_logger = std::make_shared<sm::Logger_warp>("global_Error_logger", default_format, sm::Level::ERROR);
    sm::Logger_warp::ptr global_Fatal_logger = std::make_shared<sm::Logger_warp>("global_Fatal_logger", default_format, sm::Level::FATAL);
}
