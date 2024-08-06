#include <iostream>
#include <functional>
#include <memory>
#include <ucontext.h>

namespace sm {

class Fiber : public std::enable_shared_from_this<Fiber> {
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum State {
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY
    };

private:
    Fiber(); // 默认构造函数，私有化以防止直接实例化

public:
    // 构造函数，接受一个函数作为回调，以及一个栈大小参数
    Fiber(std::function<void()> cb, size_t stacksize = 0) : m_cb(cb), m_stacksize(stacksize) {
        // 构造函数的实现细节
    }

    // 析构函数
    ~Fiber() {
        // 析构函数的实现细节
    }

    // 重置协程函数，并重置状态
    void reset(std::function<void()> cb) {
        // 重置函数的实现细节
    }

    // 切换到当前协程执行
    void swapIn() {
        // swapIn的实现细节
    }

    // 切换到后台执行
    void swapOut() {
        // swapOut的实现细节
    }

    // 返回当前协程
    static ptr GetThis() {
        // GetThis的实现细节
    }

    // 协程切换到后台，并且设置为Ready状态
    static void YieldToReady() {
        // YieldToReady的实现细节
    }

    // 协程切换到后台，并且设置为Hold状态
    static void YieldToHold() {
        // YieldToHold的实现细节
    }

    // 总协程数
    static uint64_t tTotalFibers() {
        // tTotalFibers的实现细节
    }

    static void MainFunc() {
        // MainFunc的实现细节
    }

private:
    uint64_t m_id = 0; // 协程的唯一标识符
    uint32_t m_stacksize = 0; // 协程的栈大小
    State m_state = INIT; // 协程的初始状态
    ucontext_t m_ctx; // 协程的上下文
    void* m_stack = nullptr; // 协程的栈
    std::function<void()> m_cb; // 协程要执行的回调函数
};

} // namespace sylar