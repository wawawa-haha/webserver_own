#include "util.h"
#include "loggers.h"
namespace sm {
pid_t getSystemThreadId() {
    return syscall(SYS_gettid);
}
}