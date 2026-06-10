#include <jni.h>
#include <malloc.h>      // RAM'i kökünden boşaltacak malloc_trim şalteri burada!
#include <android/log.h>

#define LOG_TAG "DeterEngine_RAM"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Ana motorun çağıracağı o meşhur RAM Temizleme şalteri
extern "C" void execute_ram_flush() {
    LOGI("[RAM Shifter]: Hafıza havuzundaki şişkinlikler tespit ediliyor...");

    // malloc_trim(0), sisteme "bana tahsis ettiğin ama şu an aktif kullanmadığım 
    // ne kadar çöp, önbellek, boşluk varsa hepsini geri al" emrini verir.
    // Parametrenin 0 olması, temizliği en agresif seviyede yap demek usta!
    if (malloc_trim(0) == 1) {
        LOGI("[RAM Shifter]: ONAY - Boş hafıza başarıyla temizlendi ve sisteme iade edildi! 🧼");
    } else {
        // 0 dönerse ya temizlenecek alan yoktur ya da sistem o an izin vermemiştir, emniyet subabı olsun
        LOGI("[RAM Shifter]: Hafıza zaten sınırlarda veya işletim sistemi şu an temizliğe izin vermedi.");
    }
}

