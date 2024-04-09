package com.example.ndktest1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.ndktest1.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'ndktest1' library on application startup.
    static {
        System.loadLibrary("ndktest123");
        System.loadLibrary("textjni_lib");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        MainActivity.static_text("我是静态方法，哈哈");
        text("我是普通方法，哈哈");

        Student student = new Student();
        student.native_Text();
    }

    /**
     * A native method that is implemented by the 'ndktest1' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int text(String message);

    public static native int static_text(String message);
}