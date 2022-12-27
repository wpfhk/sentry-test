//package com.example.testlib
//
//import android.app.ActivityManager
//import android.content.Context
//import androidx.annotation.Keep
//
//class NativeLib {
//    companion object {
//        init {
//            System.loadLibrary("testlib")
//        }
//
//        private lateinit var pContext: Context
//        @Keep
//        fun run(context: Context) {
//            pContext = context
//            initialize()
//        }
//
//        private external fun initialize()
//
//        @Keep
//        @JvmStatic
//        fun getTopActivityPackageName(): String {
//            val am = pContext.getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
//            val runningProcesses = am.runningAppProcesses
//            for (processInfo in runningProcesses) {
//                if (processInfo.importance == ActivityManager.RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
//                    for (activeProcess in processInfo.pkgList) {
//                        if (activeProcess == pContext.packageName) {
//                            return activeProcess
//                        }
//                    }
//                }
//            }
//            return ""
//        }
//    }
//}