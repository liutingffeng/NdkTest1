//
// Created by liutingfeng on 2024/4/9.
//

#include <jni.h>
#include <string>
#include <android/log.h>

jint native_text(JNIEnv *env, jobject jobject1, jstring msg) {
    const char *p_msg = env->GetStringUTFChars(msg, JNI_FALSE);
    __android_log_print(ANDROID_LOG_INFO, "mmm", "method = %s, msg = %s", __FUNCTION__, p_msg);

    return 0;
}


jint native_static_text(JNIEnv *env, jclass jclass1, jstring meg) {
    const char *p_msg = env->GetStringUTFChars(meg, JNI_FALSE);
    __android_log_print(ANDROID_LOG_INFO, "mmm", "method = %s, msg = %s", __FUNCTION__, p_msg);

    return 0;
}

static const JNINativeMethod nativeMethod[] = {
        {"text", "(Ljava/lang/String;)I", (void *) native_text},
        {"static_text", "(Ljava/lang/String;)I", (void *) native_static_text}
};

static int registNativeMethod(JNIEnv *env) {
    int result = -1;
    // 找到native方法所在的class
    jclass class_text = env ->FindClass("com/example/ndktest1/MainActivity");
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
    }
    return result;
}