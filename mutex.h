#include <semaphore.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>

namespace sm{
class Semaphore{
public:
private:
    Semaphore(const Semaphore  & v) = delete;
    Semaphore(const Semaphore  &&  v) = delete;
    Semaphore& operator =(const Semaphore& v) = delete;
private:
    sem_t m_sem;
};
}