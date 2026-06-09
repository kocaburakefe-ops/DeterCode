#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    // Direkt işlemci seviyesinden gelen saf performans mesajı
    std::string hello = "C++ Hibrit Motoru Aktif: Saf Performansla Calisiyor! 🚀";
    return env->NewStringUTF(hello.c_str());
}

