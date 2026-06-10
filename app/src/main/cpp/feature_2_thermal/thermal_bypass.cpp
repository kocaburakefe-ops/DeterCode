#include <jni.h>
#include <sched.h>       // Linux işlemci zamanlama (Scheduler) şalteri için
#include <android/log.h>

#define LOG_TAG "DeterEngine_Thermal"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Ana motorun çağıracağı o meşhur Real-Time Öncelik Enjeksiyon fonksiyonu
extern "C" void apply_thermal_priority_bypass() {
    LOGI("[Thermal Bypass]: Real-Time öncelik enjeksiyonu başlatıldı...");

    // Sistem hararet yüzünden frekans kısmaya çalışsa bile, bizim kodların önceliğini 
    // Linux'un en tepesindeki "SCHED_FIFO" (Real-Time / Canlı Yayın) moduna zorluyoruz.
    struct sched_param param;
    
    // Alabileceğimiz en yüksek rütbeyi kapıyoruz (Kraliyet muhafızı modu)
    param.sched_priority = sched_get_priority_max(SCHED_FIFO); 

    // Şu an çalışan mevcut iş parçacığını (Thread) en tepeye kelepçeliyoruz
    if (sched_setscheduler(0, SCHED_FIFO, &param) == 0) {
        LOGI("[Thermal Bypass]: ONAY - İşlemci Real-Time moduna çekildi! Telefon bizi kasamayacak! ⚡");
    } else {
        LOGE("[Thermal Bypass]: Zamanlayıcı önceliği set edilemedi. Rootsuz hat kısıtlaması olabilir.");
    }
}

