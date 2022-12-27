package com.example.testlib;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.Application;
import android.content.Context;
import android.util.Log;

import androidx.annotation.Keep;

import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import kotlin.jvm.JvmStatic;

public class NativeLib {
    private static boolean timerEnabled = true;
    private static Timer timer;
    private static TimerTask timerTask;

    public NativeLib() {
        System.loadLibrary("testlib");
    }

    public void runTestNotify() {
        testNotify();
    }

    public void runNative(Context ctx) {
        initialize(ctx);
    }

    public void start(Context ctx, int procPrio) {
        timer = new Timer();
        timerTask = new TimerTask() {
            int cnt = 0;
            @Override
            public void run() {
                android.os.Process.setThreadPriority(android.os.Process.myTid(), procPrio);
                if (!timerEnabled) {
                    try {
                        synchronized (this) {
                            this.wait();
                        }
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                isForegroundStatus(ctx);
                cnt += 1;
                Log.e("THREAD", "      myPid: " + android.os.Process.myPid());
                Log.e("THREAD", "      myTid: " + android.os.Process.myTid());
                Log.e("PRIORITY", "     priority: " + android.os.Process.getThreadPriority(android.os.Process.myTid()) + ", " + cnt);
                Log.e("Empty", "-------------------------");
            }
        };

        timer.schedule(timerTask, 0, 1000);
    }

    public void stop() {
        timerEnabled = false;
    }

    public void restart() {
        timerEnabled = true;
        synchronized (timer) {
            timer.notify();
        }
    }

    private static native void initialize(Context context);
    private static native void stopThread();
    private static native void testNotify();


    @Keep
    @JvmStatic
    public static boolean isForegroundStatus(Context context) {
        ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        List<RunningAppProcessInfo> runningAppProcesses = am.getRunningAppProcesses();
        for (RunningAppProcessInfo processInfo : runningAppProcesses) {
//            printCpuUsages();
//            ActivityManager.getMyMemoryState(processInfo);
            Log.e("MEMORY", "    current trim memory level: " + processInfo.lastTrimLevel);
            Log.e("Empty", "-------------------------");
            Log.e("ESMC", "  process name: " + processInfo.processName);
            Log.e("ESMC", "     pid: " + processInfo.pid);

            ActivityManager.MemoryInfo memoryInfo = new ActivityManager.MemoryInfo();
            Log.e("MEMORY", "     memory class: " + am.getMemoryClass());
            am.getMemoryInfo(memoryInfo);
            Log.e("MEMORY", "     total: " + memoryInfo.totalMem);
            Log.e("MEMORY", "     avail: " + memoryInfo.availMem);
            Log.e("MEMORY", "     used: " + (memoryInfo.totalMem - memoryInfo.availMem));

            if (processInfo.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
                for (String activeProcess : processInfo.pkgList) {
                    if (activeProcess.equals(context.getPackageName())) {
                        Log.e("STATE", "      current state: foreground");
                        return true;
                    }
                }
            }
        }
        Log.e("STATE", "      current state: background");
        return false;
    }
}
