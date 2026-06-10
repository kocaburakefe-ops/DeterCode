#include <jni.h>
#include <sys/resource.h> // Nice değeri (setpriority) için şart!
#include <android/log.h>

#define LOG_TAG "DeterEngine_Nice"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" void apply_nice_priority_override() {
    LOGI("[Nice Override]: Kibarlık maskesi düşürülüyor, rütbe en tepeye çekiliyor...");

    // -20 rütbesi: "Benden daha önemli işlem yok" emridir usta!
    if (setpriority(PRIO_PROCESS, 0, -20) == 0) {
        LOGI("[Nice Override]: ONAY - Öncelik rütbesi zorla -20 (Agresif) yapıldı! ⚡");
    } else {
        LOGE("[Nice Override]: Rütbe set edilemedi. Hat kısıtlaması olabilir.");
    }
}

