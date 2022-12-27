package com.example.testlib;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class TestApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        registerActivityLifecycleCallbacks(mActivityLifecycleCallbacks);
    }

    private String curState;

    public String getCurState() {
        return curState;
    }

    ActivityLifecycleCallbacks mActivityLifecycleCallbacks = new ActivityLifecycleCallbacks() {
        @Override
        public void onActivityCreated(@NonNull Activity activity, @Nullable Bundle bundle) {
            Log.e("LifecycleCallbacks", "onActivityCreated: "+activity.getLocalClassName());
            curState = "onActivityCreated";
        }

        @Override
        public void onActivityStarted(@NonNull Activity activity) {
            Log.e("LifecycleCallbacks", "onActivityStarted: "+activity.getLocalClassName());
            curState = "onActivityStarted";
        }

        @Override
        public void onActivityResumed(@NonNull Activity activity) {
            Log.e("LifecycleCallbacks", "onActivityResumed: "+activity.getLocalClassName());
            curState = "onActivityResumed";
        }

        @Override
        public void onActivityPaused(@NonNull Activity activity) {
            Log.e("LifecycleCallbacks", "onActivityPaused: "+activity.getLocalClassName());
            curState = "onActivityPaused";
        }

        @Override
        public void onActivityStopped(@NonNull Activity activity) {
            Log.e("LifecycleCallbacks", "onActivityStopped: "+activity.getLocalClassName());
            curState = "onActivityStopped";
        }

        @Override
        public void onActivitySaveInstanceState(@NonNull Activity activity, @NonNull Bundle bundle) {
            Log.e("LifecycleCallbacks", "onActivitySaveInstanceState: "+activity.getLocalClassName());
            curState = "onActivitySaveInstanceState";
        }

        @Override
        public void onActivityDestroyed(@NonNull Activity activity) {
            Log.e("LifecycleCallbacks", "onActivityDestroyed: "+activity.getLocalClassName());
            curState = "onActivityDestroyed";
        }

    };
}
