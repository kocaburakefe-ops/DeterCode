#include <jni.h>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <sys/sysinfo.h> // Linux sistem bilgilerini okumak için emniyet subabı
#include <sched.h>       // Linux çekirdeğinin işlemci zamanlama kütüphanesi
#include <unistd.h>      // Sistem çağrıları için ana şalter
#include <cstdlib>       // rand() fonksiyonu için ekledik usta

// =====================================================================
// 1. ÖZELLİK: DIŞARIDAKİ ODADAN LİMİTÖR İPTAL ŞALTERİNİ ÇAĞIRIYORUZ
// =====================================================================
extern "C" void start_core_unclogging();

// Arka planda (asenkron) yakıt pompalayan gizli fonksiyon
std::string asyncFuelPump() {
    // Ağır bir veri işleme sürecini simüle ediyoruz (Arayüzü kitlememek için arkada 2 saniye piston devredecek)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return "Asenkron Yakıt Pompası: Veri Depodan Çekildi ve Motor Ateşlendi! ⚡";
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    // 1. Paket: İşlemciden gelen saf performans mesajı
    std::string nativeMessage = "C++ Hibrit Motoru Aktif: Saf Performansla Calisiyor! 🚀";
    return env->NewStringUTF(nativeMessage.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getAsyncData(
        JNIEnv* env,
        jobject /* this */) {
    
    // 2. Paket: C++ thread mekanizması ile fonksiyonu arka planda ateşliyoruz
    auto futureResult = std::async(std::launch::async, asyncFuelPump);
    
    // Veri hazır olduğunda yakalayıp Java'ya teslim ediyoruz
    std::string finalData = futureResult.get();
    return env->NewStringUTF(finalData.c_str());
}

// YENİ ENJEKSİYON: İşlemcinin mimari yapısını ve çekirdek durumunu kontrol eder
extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getHardwareInfo(
        JNIEnv* env,
        jobject /* this */) {
    
    #if defined(__arm64__) || defined(__aarch64__)
        std::string cpuArch = "İşlemci Mimarisi: Safkan ARM64 Canavarı! 🦾";
    #else
        std::string cpuArch = "İşlemci Mimarisi: Standart/X86 Yapısı.";
    #endif

    // Linux çekirdeğinden sistem toplam RAM bilgisini çekiyoruz (Düşük seviye okuma)
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        long totalRam = (info.totalram * info.mem_unit) / (1024 * 1024);
        // USTA: std::to_std::string hatası düzeltildi, jilet gibi std::to_string yapıldı!
        cpuArch += " | Toplam Sistem RAM: " + std::to_string(totalRam) + " MB";
    }

    return env->NewStringUTF(cpuArch.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_stressTestCPU(
        JNIEnv* env,
        jobject /* this */) {

    // -----------------------------------------------------------------
    // LİMİTÖR İPTALİ TETİKLENİYOR: Bizim yeni müstakil odadaki isyanı başlatıyoruz!
    // -----------------------------------------------------------------
    start_core_unclogging();

    // 1. ADIM: Şu an hangi işlemci çekirdeğinin üzerindeyiz? Linux'tan onu öğreniyoruz.
    int currentCore = sched_getcpu();
    
    std::string report = "DeterEngine Raporu: Marş basıldı. LİMİTÖRLER İPTAL! Aktif Çekirdek: #" + std::to_string(currentCore) + " \n";

    // 2. ADIM: Dibi görelim! Seçilen çekirdeğe mikro saniyede milyonlarca döngü bindiriyoruz.
    double dummyValue = 123.45;
    auto startTime = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 5000000; i++) {
        dummyValue = dummyValue * 1.00001; // İşlemcinin kayan nokta (Floating Point) ünitesini zorluyoruz
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    report += "-> 5 Milyon işlem " + std::to_string(duration) + " milisaniyede C++ ile eritildi! 🔥";
    
    return env->NewStringUTF(report.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kocaburakefe_detercode_MainActivity_getLiveDashboardData(
        JNIEnv* env,
        jobject /* this */) {

    // 1. Linux çekirdeğinden anlık aktif çekirdeği kapıyoruz
    int activeCore = sched_getcpu();
    
    // 2. Şimdilik simüle edilmiş hararet ve RAM şamandıra verilerini ekleyiyoruz
    int temperature = 38 + (rand() % 5); // 38-42 derece arası canlı salınım
    int ramUsage = 65 + (rand() % 3);    // %65-68 arası anlık RAM dalgalanması

    // Verileri Java'nın rahatça çözebileceği bir paket (String) haline getiriyoruz
    std::string liveReport = std::to_string(activeCore) + "," + 
                             std::to_string(temperature) + "," + 
                             std::to_string(ramUsage);

    return env->NewStringUTF(liveReport.c_str());
}
