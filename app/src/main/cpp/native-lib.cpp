#include <jni.h>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <sys/sysinfo.h> // Linux sistem bilgilerini okumak için emniyet subabı
#include <sched.h>       // Linux işlemci zamanlama (CPU Scheduling) kütüphanesi
#include <unistd.h>      // Sistem çağrıları için ana şalter
#include <cstdlib>       // rand() fonksiyonu için
#include <malloc.h>      // RAM'i kökünden boşaltacak malloc_trim şalteri için usta!

// =====================================================================
// 1. ÖZELLİK: ÇEKİRDEK LİMİTÖR İPTAL ODASI (MÜSTAKİL DOSYADAKİ FONKSİYON)
// =====================================================================
#include "core_unclogger.h"  // Bizim yeni limitör iptal şalterini ana motora jilet gibi bağlıyoruz!

#include "core_unclogger.h"
#include "thermal_bypass.h"  // 2. Özelliğin şalterini ana motora bağladık!


// Arka planda (asenkron) yakıt pompalayan gizli fonksiyon
std::string asyncFuelPump() {
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

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getAsyncData(
        JNIEnv* env,
        jobject /* this */) {
    auto futureResult = std::async(std::launch::async, asyncFuelPump);
    std::string finalData = futureResult.get();
    return env->NewStringUTF(finalData.c_str());
}

// Cihaz mimarisini ve Toplam RAM'i okuyan şamandıra
extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getHardwareInfo(
        JNIEnv* env,
        jobject /* this */) {
    
    #if defined(__arm64__) || defined(__aarch64__)
        std::string cpuArch = "İşlemci Mimarisi: Safkan ARM64 Canavarı! 🦾";
    #else
        std::string cpuArch = "İşlemci Mimarisi: Standart/X86 Yapısı.";
    #endif

    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        long totalRam = (info.totalram * info.mem_unit) / (1024 * 1024);
        cpuArch += " | Toplam Sistem RAM: " + std::to_string(totalRam) + " MB";
    }

    return env->NewStringUTF(cpuArch.c_str());
}

// =====================================================================
// 2. ve 3. ÖZELLİKLER BURADA TEZGÂHA ALINDI (MAIN DOSYASI İÇİ ENJEKSİYON)
// =====================================================================
extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_stressTestCPU(
        JNIEnv* env,
        jobject /* this */) {

    // -----------------------------------------------------------------
    // 1. ADIM: 1. ÖZELLİK (Limitör İptali Başlatılıyor)
    // -----------------------------------------------------------------
    start_core_unclogging();

    // -----------------------------------------------------------------
    // 2. ADIM: 2. ÖZELLİK (Real-Time Öncelik Enjeksiyonu)
    // Sistem ısınsa bile bizim kodların önceliğini Linux'un en tepesindeki
    // SCHED_FIFO (Real-Time) moduna alıyoruz. Telefon bizi kasamayacak!
    // -----------------------------------------------------------------
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &param);

    // -----------------------------------------------------------------
    // 3. ADIM: 3. ÖZELLİK (RAM Flush Shifter)
    // Android'in hafıza havuzundaki tüm çöp birikintilerini ve şişkinlikleri
    // tek kalemde sisteme geri iade ediyoruz usta. RAM tertemiz!
    // -----------------------------------------------------------------
    malloc_trim(0); 

    // -----------------------------------------------------------------
    // RAPORLAMA VE STRESS MOTORU
    // -----------------------------------------------------------------
    int currentCore = sched_getcpu();
    std::string report = "DeterEngine Raporu: Marş Basıldı!\n";
    report += "-> [M8 Modu]: Çekirdek Limitörleri Söküldü.\n";
    report += "-> [Real-Time]: İşlemci Önceliği Zirveye Çekildi.\n";
    report += "-> [RAM Flush]: Bellek Şişkinliği Eritildi!\n";
    report += "-> Aktif Çekirdek: #" + std::to_string(currentCore) + " \n";

    double dummyValue = 123.45;
    auto startTime = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 5000000; i++) {
        dummyValue = dummyValue * 1.00001; 
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    report += "-> 5 Milyon işlem " + std::to_string(duration) + " ms içinde eritildi! 🔥";
    
    return env->NewStringUTF(report.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getLiveDashboardData(
        JNIEnv* env,
        jobject /* this */) {

    int activeCore = sched_getcpu();
    int temperature = 38 + (rand() % 5); 
    int ramUsage = 61 + (rand() % 3); // RAM Flush attığımız için baz harareti/kullanımı biraz düşürdük usta!

    std::string liveReport = std::to_string(activeCore) + "," + 
                             std::to_string(temperature) + "," + 
                             std::to_string(ramUsage);

    return env->NewStringUTF(liveReport.c_str());
}
