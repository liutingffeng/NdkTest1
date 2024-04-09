//
// Created by liutingfeng on 2024/4/9.
//
#include <jni.h>
#include <iostream>
#include <android/log.h>

static void native_init(JNIEnv *env, jobject jobject1) {
    //1 获取java对象的变量的值，并重新为他设置新的值

    //获取class对象
    jclass jclass_student = env->GetObjectClass(jobject1);
    // 从class中获取变量
    jfieldID jfieldId = env->GetFieldID(jclass_student, "name", "Ljava/lang/String;");
    //从java对象obj中获取name变量的值
    jstring name = static_cast<jstring>(env->GetObjectField(jobject1, jfieldId));
    const char *char_name = env->GetStringUTFChars(name, JNI_FALSE);
    // 打印出原来的name变量的值
    __android_log_print(ANDROID_LOG_INFO, "mmm", "method = %s, msg = %s", __FUNCTION__,
                                char_name);
    const char native_name[] = "小明";
    jstring jstring_name = env->NewStringUTF(native_name);
    // 通过jni重新设置变量name的值
    env->SetObjectField(jobject1, jfieldId, jstring_name);


    //2 调用java对象中的方法

    //获取class对象中的print方法
    jmethodID print = env->GetMethodID(jclass_student, "print", "()V");
    //调用java对象中的print方法
    env->CallVoidMethod(jobject1,print);
}

static void native_text(JNIEnv *env, jobject jobject1) {
    //获取class对象
    jclass jclass_student = env->FindClass("com/example/ndktest1/Student");
    // 从class中获取变量
    jfieldID jfieldId_text = env->GetStaticFieldID(jclass_student, "text", "Ljava/lang/String;");
    //获取静态变量text的值
    jstring text = static_cast<jstring>(env->GetStaticObjectField(jclass_student, jfieldId_text));
    const char *char_name = env->GetStringUTFChars(text, JNI_FALSE);
    __android_log_print(ANDROID_LOG_INFO, "mmm", "method = %s, msg = %s", __FUNCTION__,
                        char_name);
    jstring jstring1 = env->NewStringUTF("改过了");
    // 修改静态变量text的值
    env->SetStaticObjectField(jclass_student, jfieldId_text, jstring1);
    //获取静态方法printText
    jmethodID jmethodId = env->GetStaticMethodID(jclass_student, "printText", "()V");
    //调用静态方法printText
    env->CallStaticVoidMethod(jclass_student, jmethodId);
}


static const JNINativeMethod nativeMethod[] = {
        {"native_init", "()V", (void *) native_init},
        {"native_Text", "()V", (void *) native_text},
};

static int registNativeMethod(JNIEnv *env) {
    int result = -1;

    jclass class_text = env->FindClass("com/example/ndktest1/Student");
    if (env->RegisterNatives(class_text, nativeMethod,
                             sizeof(nativeMethod) / sizeof(nativeMethod[0])) == JNI_OK) {
        result = 0;
    }
    return result;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    int result = -1;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_1) == JNI_OK) {
        if (registNativeMethod(env) == JNI_OK) {
            result = JNI_VERSION_1_6;
        }
        return result;
    }
}