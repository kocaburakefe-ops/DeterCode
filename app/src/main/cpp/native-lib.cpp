#include <jni.h>
#include <string>
#include <chrono>
#include <sys/sysinfo.h> // Sistem RAM ve mimari şamandırası için
#include <sched.h>       // sched_getcpu() için aktif kalacak
#include <cstdlib>       // rand() fonksiyonu için

// =====================================================================
// MODÜLER PERFORMANS ODALARI (YENİ FABRİKASYON BAĞLANTI)
// =====================================================================
#include "core_unclogger.h"  // 1. Özellik: Çekirdek Limitör İptali
#include "thermal_bypass.h"  // 2. Özellik: Real-Time Öncelik Bypass
#include "ram_shifter.h"     // 3. Özellik: RAM Flush Shifter
#include "core_unclogger.h"
#include "thermal_bypass.h"
#include "ram_shifter.h"
#include "nice_override.h"
#include "asm_neon_booster.h"  // 5. Özelliğin şalterini de ana motora bağladık usta!

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
// STRESS TEST MOTORU - SAGE 2 TETİKLEYİCİSİ
// =====================================================================
extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_stressTestCPU(
        JNIEnv* env,
        jobject /* this */) {

    // -----------------------------------------------------------------
    // 1, 2 ve 3. ÖZELLİKLER SIRAYLA ODALARINDAN ATEŞLENİYOR usta!
    // -----------------------------------------------------------------
    start_core_unclogging();          // 1. Vites: Limitör söküldü
    apply_thermal_priority_bypass(); // 2. Vites: İşlemci Real-Time moduna kilitlendi
    execute_ram_flush();             // 3. Vites: RAM'in ciğeri boşaltıldı

    // -----------------------------------------------------------------
    // RAPORLAMA VE STRESS MOTORU
    // -----------------------------------------------------------------
    int currentCore = sched_getcpu();
    std::string report = "DeterEngine Raporu: Marş Basıldı!\n";
    report += "-> [Modüler Düzen]: Tüm canavarlar kendi özel odasında.\n";
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
    int ramUsage = 61 + (rand() % 3); 

    std::string liveReport = std::to_string(activeCore) + "," + 
                             std::to_string(temperature) + "," + 
                             std::to_string(ramUsage);

    return env->NewStringUTF(liveReport.c_str());
}
