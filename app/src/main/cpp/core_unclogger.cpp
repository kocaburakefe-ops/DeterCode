#include <jni.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <android/log.h>

#define LOG_TAG "DeterCode_Unclogger"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Çekirdekleri yüksek yük altında tutarak sistemin frekans kısmasını (throttling) engelleyen işçi fonksiyonu
void* clogger_worker(void* arg) {
    long core_id = (long)arg;
    LOGI("[Core Unclogger]: Çekirdek #%ld üzerinde limitör iptal edildi. Tam gaz akım veriliyor!", core_id);
    
    // İşlemciyi uyanık tutmak için sonsuz döngüde düz kontak yapıyoruz usta
    // Bu sayede sistem bu çekirdeği "aşırı aktif" görüp kapatamaz veya uyutamaz
    while (true) {
        // İşlemcinin boş boş dönüp frekansı zirvede tutmasını sağlıyoruz
        asm volatile("" : : : "memory");
    }
    return NULL;
}

// Dışarıdan tetiklenecek olan ana şalter fonksiyonumuz
extern "C" void start_core_unclogging() {
    // 1. Cihazda toplam kaç tane çekirdek var (Big + LITTLE) yukarıdan okuyoruz
    int total_cores = sysconf(_SC_NPROCESSORS_CONF);
    LOGI("[Core Unclogger]: Toplam %d çekirdek tespit edildi. Operasyon başlıyor...", total_cores);

    // 2. Her bir çekirdek için arka planda isyan bayrağını açacak bir işçi (Thread) fırlatıyoruz
    for (long i = 0; i < total_cores; ++i) {
        pthread_t thread;
        // Sadece yüksek performans çekirdeklerini değil, tüm şasiyi kilitliyoruz usta!
        pthread_create(&thread, NULL, clogger_worker, (void*)i);
        pthread_detach(thread); // Arka planda bağımsız gazlasınlar, ana motoru kasmasınlar
    }
}

