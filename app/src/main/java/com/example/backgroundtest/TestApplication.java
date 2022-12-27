package com.example.backgroundtest;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class TestApplication extends Application {
    @Override
    public void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        registerActivityLifecycleCallbacks(new ActivityLifecycleCallbacks() {
            @Override
            public void onActivityCreated(@NonNull Activity activity, @Nullable Bundle bundle) {
                Log.e("LifecycleCallbacks", "onActivityCreated: ");
                curState = "onActivityCreated";
            }

            @Override
            public void onActivityStarted(@NonNull Activity activity) {
                Log.e("LifecycleCallbacks", "onActivityStarted: ");
                curState = "onActivityStarted";
            }

            @Override
            public void onActivityResumed(@NonNull Activity activity) {
                Log.e("LifecycleCallbacks", "onActivityResumed: ");
                curState = "onActivityResumed";
            }

            @Override
            public void onActivityPaused(@NonNull Activity activity) {
                Log.e("LifecycleCallbacks", "onActivityPaused: ");
                curState = "onActivityPaused";
            }


            @Override
            public void onActivityStopped(@NonNull Activity activity) {
                Log.e("LifecycleCallbacks", "onActivityStopped: ");
                curState = "onActivityStopped";
            }

            @Override
            public void onActivitySaveInstanceState(@NonNull Activity activity, @NonNull Bundle bundle) {
                Log.e("LifecycleCallbacks", "onActivitySaveInstanceState: ");
                curState = "onActivitySaveInstanceState";
            }

            @Override
            public void onActivityDestroyed(@NonNull Activity activity) {
                Log.e("LifecycleCallbacks", "onActivityDestroyed: ");
                curState = "onActivityDestroyed";
            }

        });
    }
    @Override
    public void onCreate() {
        super.onCreate();
        registerActivityLifecycleCallbacks(mActivityLifecycleCallbacks);
    }

    private String curState;

    public String getCurState() {
        return curState;
    }

//    ActivityLifecycleCallbacks mActivityLifecycleCallbacks2 = new ActivityLifecycleCallbacks() {
//        @Override
//        public void onActivityCreated(@NonNull Activity activity, @Nullable Bundle bundle) {
//            Log.e("LifecycleCallbacks", "onActivityCreated: ");
//            curState = "onActivityCreated";
//        }
//
//        @Override
//        public void onActivityStarted(@NonNull Activity activity) {
//            Log.e("LifecycleCallbacks", "onActivityStarted: ");
//            curState = "onActivityStarted";
//        }
//
//        @Override
//        public void onActivityResumed(@NonNull Activity activity) {
//            Log.e("LifecycleCallbacks", "onActivityResumed: ");
//            curState = "onActivityResumed";
//        }
//
//        @Override
//        public void onActivityPaused(@NonNull Activity activity) {
//            Log.e("LifecycleCallbacks", "onActivityPaused: ");
//            curState = "onActivityPaused";
//        }
//
//        @Override
//        public void onActivityStopped(@NonNull Activity activity) {
//            Log.e("LifecycleCallbacks", "onActivityStopped: ");
//            curState = "onActivityStopped";
//        }
//
//        @Override
//        public void onActivitySaveInstanceState(@NonNull Activity activity, @NonNull Bundle bundle) {
//            Log.e("LifecycleCallbacks", "onActivitySaveInstanceState: ");
//            curState = "onActivitySaveInstanceState";
//        }
//
//        @Override
//        public void onActivityDestroyed(@NonNull Activity activity) {
//            Log.e("LifecycleCallbacks", "onActivityDestroyed: ");
//            curState = "onActivityDestroyed";
//        }
//
//    };

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

