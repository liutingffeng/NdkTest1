package com.example.ndktest1;

import android.util.Log;

public class Student {

    public String name = "小红";
    public static String text = "没改过";

    static {
        System.loadLibrary("studentlib");
    }

    native void native_init();
    native void native_Text();

    public Student() {
        native_init();
    }

    public void print() {
        Log.d("mmm", name);
    }

    public static void printText() {
        Log.d("mmm", text);
    }
}
