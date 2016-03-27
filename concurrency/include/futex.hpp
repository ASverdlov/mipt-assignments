#ifndef _FUTEX_H_

#include <iostream>
#include <atomic>
#include <thread>
#include <exception>
#include <chrono>

using std::atomic;
using std::thread;
using namespace std::chrono;

class futex {
private:
    atomic<int> m_counter;
    atomic<thread::id> m_locked_by;

public:
    futex(const futex&) = delete;
    futex(futex&&) = delete;
    futex& operator=(const futex&) = delete;

    futex() : m_counter(0) {}

    void lock() {
        while (m_counter.load()) {
            ;
        }
        m_locked_by.store(std::this_thread::get_id());
        m_counter++;
    }

    void unlock() {
        if (!m_counter.load()) {
            throw std::logic_error("unlock() on non-locked futex is prohibited");
        }
        if (std::this_thread::get_id() != m_locked_by.load()) {
            throw std::logic_error("unlock() on another thread's lock is prohibited");
        }
        m_counter--;
    }
};

#endif
