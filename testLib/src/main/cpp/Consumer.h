//
// Created by YoungSang on 2022/11/08.
//

#ifndef BACKGROUNDTEST_CONSUMER_H
#define BACKGROUNDTEST_CONSUMER_H

template<typename OBJ>
class Consumer {
public:
    using MyProducer = Producer<std::string>;
    Consumer(std::shared_ptr<NotifyQueue<OBJ>> pnotify_queue) : pnotify_queue_(pnotify_queue)
    {

    }

    void execute(std::function<void(const OBJ& obj)> phandle) {
        do {
            OBJ obj;
            auto bsuccess = pnotify_queue_->pop(obj);
            if (bsuccess) phandle(obj);
        } while (pnotify_queue_->isRunning());
    }
private:
    std::shared_ptr<NotifyQueue<OBJ>> pnotify_queue_;
};

#endif //BACKGROUNDTEST_CONSUMER_H
