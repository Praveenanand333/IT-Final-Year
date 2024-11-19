package com.anand.simpleapp

import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.ProgressBar
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity(), View.OnClickListener {
    private lateinit var btnAdd: Button
    private lateinit var btnSubtract: Button
    private lateinit var btnMultiply: Button
    private lateinit var etA: EditText
    private lateinit var etB: EditText
    private lateinit var result: TextView
    private lateinit var btnDivide: Button
    private lateinit var navigatebtn : Button
    private lateinit var loadingBar: ProgressBar

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.divide)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        btnAdd = findViewById(R.id.plus)
        btnSubtract = findViewById(R.id.minus)
        btnMultiply = findViewById(R.id.multiply)
        etA = findViewById(R.id.numbera)
        etB = findViewById(R.id.numberb)
        result = findViewById(R.id.result)
        btnDivide = findViewById(R.id.dividebtn)
        navigatebtn = findViewById(R.id.navigatebtn)
        loadingBar=findViewById(R.id.progressBar)

        btnAdd.setOnClickListener(this)
        btnSubtract.setOnClickListener(this)
        btnMultiply.setOnClickListener(this)
        btnDivide.setOnClickListener(this)

        navigatebtn.setOnClickListener {
            loadingBar.visibility = ProgressBar.VISIBLE
            Thread {
                Thread.sleep(1000)
                runOnUiThread {
                    loadingBar.visibility = ProgressBar.VISIBLE
                    val intent = Intent(this, SecondActivity::class.java)
                    startActivity(intent)
                }
            }.start()
        }
    }

    override fun onClick(v: View?) {
        val a = etA.text.toString().toIntOrNull() ?: 0
        val b = etB.text.toString().toIntOrNull() ?: 0
        var resultVar = 0
        when (v?.id) {
            R.id.plus -> resultVar = a + b
            R.id.minus -> resultVar = a - b
            R.id.multiply -> resultVar = a * b
            R.id.divide ->resultVar=a/b;
        }
        result.text = "Result is $resultVar"

    }

    

    
}
