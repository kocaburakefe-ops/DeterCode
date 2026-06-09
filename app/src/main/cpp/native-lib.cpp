#include <jni.h>
#include <string>
#include <thread>
#include <future>
#include <chrono>

// Arka planda (asenkron) yakıt pompalayan gizli fonksiyon
std::string asyncFuelPump() {
    // Ağır bir veri işleme sürecini simüle ediyoruz (Örn: Buluttan veri çekme veya analiz)
    // Ana arayüzü kitlememek için arka planda 2 saniye piston devredecek
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return "Asenkron Yakıt Pompası: Veri Depodan Çekildi ve Motor Ateşlendi! ⚡";
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string nativeMessage = "C++ Hibrit Motoru Aktif: Saf Performansla Calisiyor! 🚀";
    return env->NewStringUTF(nativeMessage.c_str());
}

// YENİ ENJEKSİYON: Java tarafına asenkron veriyi fırlatan köprü
extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getAsyncData(
        JNIEnv* env,
        jobject /* this */) {
    
    // C++ thread mekanizması ile fonksiyonu arka planda ateşliyoruz
    auto futureResult = std::async(std::launch::async, asyncFuelPump);
    
    // Veri hazır olduğunda yakalayıp Java'ya teslim ediyoruz
    std::string finalData = futureResult.get();
    return env->NewStringUTF(finalData.c_str());
}
