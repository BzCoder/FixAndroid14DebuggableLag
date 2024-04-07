package com.example.fixandroid14debuggablelag

import android.os.Bundle
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import me.bzcoder.fixandroid14debuggablelag.FixTools
import kotlin.system.measureTimeMillis

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
        testDouble1()
        FixTools().fixAndroid14DebuggableLag()
        testDouble2()
    }


    private fun testDouble1() {
        val items = (1..1000000).map {
            "${it}.0001"
        }
        measureTimeMillis {
            items.forEach { str ->
                val d = str.toDouble()
            }
        }.let {
            val tvCostTime = findViewById<TextView>(R.id.tvCostTime1)
            tvCostTime.text = "before hook Double spend: $it ms"
        }
    }



    private fun testDouble2() {
        val items = (1..1000000).map {
            "${it}.0001"
        }
        measureTimeMillis {
            items.forEach { str ->
                val d = str.toDouble()
            }
        }.let {
            val tvCostTime = findViewById<TextView>(R.id.tvCostTime2)
            tvCostTime.text = "after hook Double spend: $it ms"

        }
    }

}

