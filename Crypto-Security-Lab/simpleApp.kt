package com.anand.simpleapp


//  <uses-permission android:name="android.permission.POST_NOTIFICATIONS" />

import android.content.Intent
import android.app.NotificationChannel
import android.app.NotificationManager
import android.os.Build
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.ProgressBar
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat


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

    private val CHANNEL_ID = "result_notification"
    private val NOTIFICATION_ID = 1

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)

        // Set padding for edge-to-edge
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.divide)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        // Initialize Views
        btnAdd = findViewById(R.id.plus)
        btnSubtract = findViewById(R.id.minus)
        btnMultiply = findViewById(R.id.multiply)
        etA = findViewById(R.id.numbera)
        etB = findViewById(R.id.numberb)
        result = findViewById(R.id.result)
        btnDivide = findViewById(R.id.dividebtn)
        navigatebtn = findViewById(R.id.navigatebtn)
        loadingBar=findViewById(R.id.progressBar)
        // Set OnClickListener for buttons
        btnAdd.setOnClickListener(this)
        btnSubtract.setOnClickListener(this)
        btnMultiply.setOnClickListener(this)
        btnDivide.setOnClickListener(this)
        // Create a notification channel
        createNotificationChannel()
        navigatebtn.setOnClickListener {
            loadingBar.visibility = ProgressBar.VISIBLE
            Thread {
                Thread.sleep(1000)
                runOnUiThread {
                    loadingBar.visibility = ProgressBar.VISIBLE
                    val intent = Intent(this, SecondActivity::class.java)
                    startActivity(intent) // Start the SecondActivity
                }
            }.start()
        }
    }

    override fun onClick(v: View?) {
        // Get input values and ensure they're valid integers
        val a = etA.text.toString().toIntOrNull() ?: 0
        val b = etB.text.toString().toIntOrNull() ?: 0
        var resultVar = 0

        when (v?.id) {
            R.id.plus -> resultVar = a + b
            R.id.minus -> resultVar = a - b
            R.id.multiply -> resultVar = a * b
            R.id.divide ->resultVar=a/b;
        }

        // Display the result
        result.text = "Result is $resultVar"

        // Show notification
        showResultNotification(resultVar)
    }

    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val name = "Result Notification"
            val descriptionText = "Notification for calculation results"
            val importance = NotificationManager.IMPORTANCE_DEFAULT
            val channel = NotificationChannel(CHANNEL_ID, name, importance).apply {
                description = descriptionText
            }
            // Register the channel with the system
            val notificationManager: NotificationManager =
                getSystemService(NOTIFICATION_SERVICE) as NotificationManager
            notificationManager.createNotificationChannel(channel)
        }
    }

    private fun showResultNotification(resultVar: Int) {
        val notification = NotificationCompat.Builder(this, CHANNEL_ID)
            .setSmallIcon(R.drawable.ic_launcher_background) // Ensure you have a drawable icon named ic_notification
            .setContentTitle("Calculation Result")
            .setContentText("The result of your calculation is $resultVar")
            .setPriority(NotificationCompat.PRIORITY_DEFAULT)
            .build()

        with(NotificationManagerCompat.from(this)) {
            notify(NOTIFICATION_ID, notification)
        }
    }
}
