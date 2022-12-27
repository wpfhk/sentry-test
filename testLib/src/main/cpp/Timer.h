//
// Created by YoungSang on 2022/10/26.
//

#ifndef BACKGROUNDTEST_TIMER_H
#define BACKGROUNDTEST_TIMER_H

#include <thread>
#include <chrono>
#include <functional>
#include <cstdio>
#include <atomic>

class Timer {
public:
    Timer() : cnt(0) {}
    ~Timer() {
        if (mRunning) {
            stop();
        }
    }
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(int)> Timeout;

    void start(const Interval &interval, const Timeout &timeout) {
        mRunning = true;

        mThread = std::thread([this, &interval, &timeout] {
            while (mRunning) {
//                getrusage(RUSAGE_THREAD, &mStart);
                std::this_thread::sleep_for(interval);
//                getrusage(RUSAGE_THREAD, &mEnd);
                cnt++;
                timeout(cnt);
            }
        });
    }
    void stop() {
        mRunning = false;
        mThread.join();
    }

private:
    std::thread mThread{};
    std::atomic_bool mRunning{};
    int cnt;
};

#endif //BACKGROUNDTEST_TIMER_H
