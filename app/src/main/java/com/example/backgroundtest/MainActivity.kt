package com.example.backgroundtest

import android.os.Bundle
import android.util.Log
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.example.testlib.NativeLib
import com.example.testlib.TestApplication

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val nativeLib = NativeLib()
        nativeLib.runTestNotify()
        val btnStop = findViewById<Button>(R.id.btnStop)
        val btnRestart = findViewById<Button>(R.id.btnRestart)
        btnStop.setOnClickListener {
            Log.e("MAIN", "stop thread")
            nativeLib.stop()
        }
        btnRestart.setOnClickListener {
            Log.e("MAIN", "restart thread")
            nativeLib.restart()
        }
//        nativeLib.runNative(applicationContext)
//        nativeLib.start(applicationContext, Process.THREAD_PRIORITY_LOWEST)    // 0

//        val a = NativeLib(application)
//        a.start(applicationContext, Process.THREAD_PRIORITY_DISPLAY)     // 10
//        val b = NativeLib(application)
//        b.start(applicationContext, Process.THREAD_PRIORITY_DEFAULT)          //-16
//        val c = NativeLib(application)
//        c.start(applicationContext, Process.THREAD_PRIORITY_BACKGROUND)        // -4
//        val d = NativeLib()
//        d.start(applicationContext, Process.THREAD_PRIORITY_FOREGROUND)     // -2
//        val e = NativeLib()
//        e.start(applicationContext, Process.THREAD_PRIORITY_LOWEST)         // -19
//        val f = NativeLib()
//        f.start(applicationContext, Process.THREAD_PRIORITY_MORE_FAVORABLE) // -1
//        val g = NativeLib()
//        g.start(applicationContext, Process.THREAD_PRIORITY_LESS_FAVORABLE) // 1
//        val h = NativeLib()
//        h.start(applicationContext, Process.THREAD_PRIORITY_URGENT_DISPLAY) // -8
//        val i = NativeLib()
//        i.start(applicationContext, Process.THREAD_PRIORITY_URGENT_AUDIO)   // -19
//        val j = NativeLib()
//        j.start(applicationContext, Process.THREAD_PRIORITY_DEFAULT)        // 0
    }

    override fun onDestroy() {
        println("finish")
        super.onDestroy()
    }
}