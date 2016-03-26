#include <iostream>
#include <atomic>

using std::atomic;

class futex {
private:
    atomic<int> m_counter;

public:
    futex(const futex&) = delete;
    futex& operator=(const futex&) = delete;

    futex() : m_counter(0) {}

    void lock() {
        while (m_counter.load()) {
            ;
        }
        m_counter++;
    }

    void unlock() {
        m_counter--;
    }
};

int main() {
    futex f;

    f.lock();
    f.lock();
    f.unlock();

    return 0;
}
