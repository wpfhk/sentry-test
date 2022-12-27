#include <jni.h>
#include <android/log.h>
#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>

//#include <cstdlib>
#include <sstream>
#include <vector>
#include <linux/oom.h>
#include <android/native_activity.h>
#include "Timer.h"
#include "NotifyQueue.h"
#include "CommonNotifyQueue.h"
#include "PrintMsgManager.h"
#include "Producer.h"
#include "Consumer.h"
#include <sentry.h>

//
// Created by YoungSang on 2022/10/06.
//

JavaVM* gJvm = nullptr;
jobject classLoader;
jmethodID findClassMethod;
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "native", __VA_ARGS__)
bool isBackground;
bool threadEnabled;

JNIEnv* getEnv();

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *pjvm, void *reserved) {
//    sentry_options_t *options = sentry_options_new();
//    sentry_options_set_dsn(options, "https://258b41b1d868476f907f676f71da4e6b@o4504371423019008.ingest.sentry.io/4504371425247233");
//    // This is also the default-path. For further information and recommendations:
//    // https://docs.sentry.io/platforms/native/configuration/options/#database-path
//    sentry_options_set_database_path(options, ".sentry-native");
//    sentry_options_set_release(options, "my-project-name@2.3.12");
//    sentry_options_set_debug(options, 1);
//    sentry_init(options);
//
//    sentry_capture_event(sentry_value_new_message_event(
//            /*   level */ SENTRY_LEVEL_INFO,
//            /*  logger */ "custom",
//            /* message */ "youngsang test"
//    ));
//
//    sentry_close();

    gJvm = pjvm;  // cache the JavaVM pointer
    JNIEnv* env;
    if(pjvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    auto nativeLibClass = env->FindClass("com/example/testlib/NativeLib");
    auto classClass = env->GetObjectClass(nativeLibClass);
    auto classLoaderClass = env->FindClass("java/lang/ClassLoader");
    auto getClassLoaderMethod = env->GetMethodID(classClass, "getClassLoader",
                                                 "()Ljava/lang/ClassLoader;");
    classLoader = env->CallObjectMethod(nativeLibClass, getClassLoaderMethod);
    findClassMethod = env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    classLoader = env->NewGlobalRef(classLoader);

    return JNI_VERSION_1_6;
}

jclass findClass(const char *name) {
    return static_cast<jclass>(getEnv()->CallObjectMethod(classLoader, findClassMethod,
                                                          getEnv()->NewStringUTF(name)));
}

bool checkIfBackground(JNIEnv* env, jobject ctx) {
    auto nativeLibClassId = findClass("com/example/testlib/NativeLib");
    jmethodID getTopActivityPackageNameId = env->GetStaticMethodID(nativeLibClassId, "isForegroundStatus",
                                                                   "(Landroid/content/Context;)Z");
    auto res = env->CallStaticBooleanMethod(nativeLibClassId, getTopActivityPackageNameId, ctx);
    return static_cast<bool>(res);
//    __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "thread status %d", static_cast<bool>(res));
}

JNIEnv* getEnv() {
    JNIEnv *env;
    int status = gJvm->GetEnv((void**)&env, JNI_VERSION_1_6);
    if(status < 0) {
        status = gJvm->AttachCurrentThread(&env, nullptr);
        if(status < 0) {
            return nullptr;
        }
    }
    return env;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testlib_NativeLib_initialize(JNIEnv *env, jclass clazz, jobject ctx) {
    //start thread1
    threadEnabled = true;
    ctx = env->NewGlobalRef(ctx);
    Timer tm1, tm2, tm3, tm4;
    double cpuTimeSec1 = 0, processTimeSec1 = 0;
//    tm1.start(std::chrono::milliseconds(1000), [&](int cnt){
////        env = getEnv();
////        auto res = checkIfBackground(env, ctx);
////        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "thread1 status %d, %d", res, cnt);
//        // cpu core 수
//        auto numCores = sysconf(_SC_NPROCESSORS_CONF);
//        double clockSpeedHz = sysconf(_SC_CLK_TCK);
//        std::chrono::milliseconds uptimeSec(0u);
//        struct sysinfo sysInfo{};
//        if (!sysinfo(&sysInfo)) {
//            uptimeSec = std::chrono::milliseconds(
//                    static_cast<unsigned long long>(sysInfo.uptime)*1000ULL/1000
//                    );
//        }
//        LOGE("uptimeSec: %llu", uptimeSec.count());
//        auto fd = open("/proc/self/stat", O_RDONLY);
//        std::vector<uint8_t> buf(512);
//        uint8_t *p = buf.data();
//        char b;
//        ssize_t bytes_read = 0;
//        std::string res;
//        std::vector<std::string> statInfo;
//
//        do {
//            read(fd, &b, 1);
//            if (b == ' ') {
//                p += 1;
//                statInfo.push_back(res);
//                res = "";
//            } else if (b == '\n') {
//                break;
//            }
//            *(p++) = b;
//            res += b;
//            bytes_read += 1;
//        } while (bytes_read < (512 - 1));
//        char * pos = nullptr;
//        int utime, stime;
//        std::stringstream ss1(statInfo.at(13));
//        ss1 >> utime;
//        std:: stringstream ss2(statInfo.at(14));
//        ss2 >> stime;
//        double cpuTimeSec2 = (utime + stime) / clockSpeedHz;
//        auto startTime = std::stoi(statInfo.at(21));
//        LOGE("utime, stime, clockSpeedHz, startTime(고정값): %d, %d, %f, %d", utime, stime, clockSpeedHz, startTime);
//        auto processTimeSec2 = uptimeSec.count() - (startTime / clockSpeedHz);
//        auto avgUsagePercent = 100 * (cpuTimeSec2 / processTimeSec2) / numCores;
//        LOGE("core: %ld\ncpu time2(sec): %.6f\n process time2(sec): %f\n average usage(sec): %.6f", numCores, cpuTimeSec2, processTimeSec2, avgUsagePercent);
//        LOGE("cpu time1, process time1: %.6f, %.6f", cpuTimeSec1, processTimeSec1);
//        if (cpuTimeSec1 != 0 && processTimeSec1 != 0) {
//            auto cpuTimeDeltaSec = cpuTimeSec2 - cpuTimeSec1;
//            auto processTimeDeltaSec = processTimeSec2 - processTimeSec1;
//            auto relAvgUsagePercent = 100 * (cpuTimeDeltaSec / processTimeDeltaSec) / numCores;
//            LOGE("상대 평균 CPU 사용량: 100 * (%.6f / %.6f) / %ld = %.6f\n\n", cpuTimeDeltaSec, processTimeDeltaSec, numCores, relAvgUsagePercent);
//        }
//        cpuTimeSec1 = cpuTimeSec2;
//        processTimeSec1 = processTimeSec2;
//    });
//    tm2.start(std::chrono::milliseconds(1000), [&](int cnt){
//        env = getEnv();
////        auto res = checkIfBackground(env, ctx);
//        auto fd = open("/proc/self/oom_score", O_RDONLY);
//        auto fd_adj0 = open("/proc/self/oom_score_adj", O_RDONLY);
//        auto fd_adj1 = open("/proc/self/oom_adj", O_RDONLY);
//        std::string oomScore;
//        std::string oomScoreAdj0;
//        std::string oomScoreAdj1;
//        char b, b0, b1;
//        ssize_t readSize, readSize0, readSize1;
//        do {
//            readSize = read(fd, &b, 1);
//            if (b == ' ' || b == '\n' || b == '\t') {
//                readSize = 0;
//            }
//            oomScore += b;
//            readSize0 = read(fd_adj0, &b0, 1);
//            if (b0 == ' ' || b0 == '\n' || b0 == '\t') {
//                readSize = 0;
//            }
//            oomScoreAdj0 += b0;
//            readSize1 = read(fd_adj1, &b1, 1);
////            if (b1 == ' ' || b1 == '\n' || b1 == '\t') {
////                break;
////            }
//            oomScoreAdj1 += b1;
//        } while (readSize > 0);
//        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "oom score: %s, %d", oomScore.c_str(), cnt);
//        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "oom score adj: %s, %d", oomScoreAdj0.c_str(), cnt);
//        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "oom adj: %s, %d", oomScoreAdj1.c_str(), cnt);
//    });
    tm3.start(std::chrono::milliseconds(1000), [&](int cnt){
        env = getEnv();
        auto res = checkIfBackground(env, ctx);
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "thread3 status %d, %d", res, cnt);
    });
//    int score2 = -15;
//    tm4.start(std::chrono::milliseconds(1000), [&](int cnt){
//        env = getEnv();
//        std::string path = "/proc/self/oom_adj";
//        std::ofstream writeFile(path.data());
//
//        if (writeFile.is_open()) {
//            score2 -= 1;
//            writeFile << score2;
//            writeFile.close();
//        }
//
//        std::ifstream openFile(path.data());
//        if (openFile.is_open()) {
//            std::string line;
////            while(getline(openFile, line)) {
////                __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "oom_adj: %s, %d", line.c_str(), cnt);
////            }
//            openFile.close();
//        }
////        auto res = checkIfBackground(env, ctx);
////        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "thread4 status %d, %d", res, cnt);
//    });
    std::this_thread::sleep_for(std::chrono::minutes(10));
//    std::thread th1 = std::thread([&] {
//        env = getEnv();
//        while(threadEnabled) {
////            checkIfBackground(env, ctx);
//            isBackground = true;
////            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        }
//    });
//
//    //waiting for finish of the thread1
//    if (th1.joinable()) {
//        th1.join();
//    }


}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_testlib_NativeLib_stopThread(JNIEnv *env, jclass clazz) {
    threadEnabled = false;
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_testlib_NativeLib_testNotify(JNIEnv *env, jclass clazz) {
    using namespace std::chrono_literals;

    auto cnt = 4;
    PrintMsgManager printMsgManager(cnt);
    LOGE("Start PrintMsgManager Background Thread %d", cnt);

    for (auto i=1; i <= 1000; ++i) {
        printMsgManager.push(std::to_string(i));
    }

    std::this_thread::sleep_for(1ms);

    printMsgManager.stop();

    LOGE("Notify stop signal");

    std::this_thread::sleep_for(1s);

    printMsgManager.rerun();

    LOGE("Notify rerun signal");

    std::this_thread::sleep_for(1s);

    printMsgManager.join();

    LOGE("All thread joinable.....");
    LOGE("After 3sec Application Exit");
    std::this_thread::sleep_for(3s);
}