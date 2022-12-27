//
// Created by YoungSang on 2022/11/08.
//

#ifndef BACKGROUNDTEST_PRINTMSGMANAGER_H
#define BACKGROUNDTEST_PRINTMSGMANAGER_H

#include "CommonNotifyQueue.h"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "native", __VA_ARGS__)

inline std::string className(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos)
        return "::";
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = colons - begin;

    return prettyFunction.substr(begin,end);
}

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)

class PrintMsgManager : public CommonNotifyQueue<std::string> {
public:
    using Object = std::string;

    PrintMsgManager(size_t run_thread_count = 1) : CommonNotifyQueue<std::string>(run_thread_count) {}
    virtual ~PrintMsgManager() {}

    void runExecute(const std::string& obj) override {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        LOGE("ThreadId[%s] Processing ==> %s", oss.str().c_str(), obj.c_str());
        LOGE("class name: %s", className(__PRETTY_FUNCTION__).c_str());
    }
};

#endif //BACKGROUNDTEST_PRINTMSGMANAGER_H
