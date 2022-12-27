//
// Created by YoungSang on 2022/11/08.
//

#ifndef BACKGROUNDTEST_NOTIFYQUEUE_H
#define BACKGROUNDTEST_NOTIFYQUEUE_H

#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <shared_mutex>
#include <mutex>

template <typename T>
class NotifyQueue {
public:
    using Container = std::queue<T>;
    NotifyQueue() : is_run_(true) {};
    virtual ~NotifyQueue() {};

    bool empty() {
        std::shared_lock<std::shared_mutex> sl(sm_);
        return queue_.empty();
    }

    bool pop(T& obj) {
        std::unique_lock<std::shared_mutex> ul(sm_);
        cv_.wait(ul, [this] {
            return (!queue_.empty() || !is_run_);
        });

        if (!is_run_) {
            return false;
        }

        if (!queue_.empty()) {
            obj = queue_.front();
            queue_.pop();
            return true;
        }

        return false;
    }

    void push(const T& obj) {
        {
            std::unique_lock<std::shared_mutex> ul(sm_);
            queue_.push(obj);
        }
        cv_.notify_one();
    }

    void notifyAll() {
        cv_.notify_all();
    }

    size_t size() {
        std::shared_lock<std::shared_mutex> sl(sm_);
        return queue_.size();
    }

    bool isRunning() {
        return is_run_;
    }

    void stop() {
        std::unique_lock<std::shared_mutex> ul(sm_);
        is_run_ = false;
        notifyAll();
    }

    void rerun() {
        std::unique_lock<std::shared_mutex> ul(sm_);
        is_run_ = true;
        notifyAll();
    }

private:
    Container               queue_;
    std::condition_variable_any cv_;
    std::shared_mutex       sm_;
    bool                    is_run_;
};

#endif //BACKGROUNDTEST_NOTIFYQUEUE_H
