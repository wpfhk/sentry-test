//
// Created by YoungSang on 2022/11/08.
//

#ifndef BACKGROUNDTEST_PRODUCER_H
#define BACKGROUNDTEST_PRODUCER_H

#include "NotifyQueue.h"

template<typename OBJ>
class Producer {
public:
    using obj = OBJ;
    Producer(std::shared_ptr<NotifyQueue<OBJ>> pnotify_queue) : pnotify_queue_(pnotify_queue) {
    }

    void push(const OBJ& str) {
        pnotify_queue_->push(str);
    }

private:
    std::shared_ptr<NotifyQueue<OBJ>> pnotify_queue_;

};

#endif //BACKGROUNDTEST_PRODUCER_H
