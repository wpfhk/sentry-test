//
// Created by YoungSang on 2022/11/08.
//

#include "NotifyQueue.h"
#include "Producer.h"
#include "Consumer.h"

#ifndef BACKGROUNDTEST_COMMONNOTIFYQUEUE_H
#define BACKGROUNDTEST_COMMONNOTIFYQUEUE_H

template<typename T>
class CommonNotifyQueue {
public:
    CommonNotifyQueue(size_t runThreadCnt = 1) : execute_(nullptr) {
        notify_ = std::make_shared<NotifyQueue<T>>();
        producer_ = std::make_shared<Producer<T>>(notify_);
        consumer_ = std::make_shared<Consumer<T>>(notify_);

        for (auto i=0; i<runThreadCnt; ++i) {
            run();
        }
    }
    virtual ~CommonNotifyQueue() {}

    void push(T&& obj) {
        push(obj);
    }

    void push(const T& obj) {
        producer_->push(obj);
    }

    virtual void runExecute(const T& obj) = 0;

    void run() {
        thread_group_.template emplace_back([this] {
           consumer_->execute([this](const T& obj) {
               runExecute(obj);
           });
        });
    }

    void stop() {
        notify_->stop();
    }

    void rerun() {
        notify_->rerun();
    }

    void join() {
        for (auto& t : thread_group_) {
            t.join();
        }
    }

private:
    std::shared_ptr<NotifyQueue<T>> notify_;
    std::shared_ptr<Producer<T>> producer_;
    std::shared_ptr<Consumer<T>> consumer_;
    std::vector<std::thread> thread_group_;
    std::function<void(const T&)> execute_;
};

#endif //BACKGROUNDTEST_COMMONNOTIFYQUEUE_H
