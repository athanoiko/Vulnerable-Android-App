package com.oiko.vulnerableapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    TextView myTextView1;

    static {
        System.loadLibrary("nativelib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myTextView1 = findViewById(R.id.myTextView1);
        myTextView1.setText("Hello world!");

        Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                call_stringFromJNI();
            }
        });

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                setText("Hello from Java world!");
            }
        });
    }

    void call_stringFromJNI(){
        myTextView1.setText(stringFromJNI());
    }

    void setText(String input){
        myTextView1.setText(input);
    }

    public native String stringFromJNI();
    public native int fuzzTest3(String data, int len);
}