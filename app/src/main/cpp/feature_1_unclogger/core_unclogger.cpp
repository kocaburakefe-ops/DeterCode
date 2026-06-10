#include <jni.h>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <sched.h>
#include <unistd.h>
#include <android/log.h>

#define LOG_TAG "DeterEngine_Unclogger"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Her bir uykucu çekirdek için arkada dönecek olan amele fonksiyonu
void clogger_worker(int core_id) {
    // 1. İşçiyi Linux çekirdeğinde hedef çekirdeğe (core_id) kelepçeliyoruz
    cpu_set_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    
    // Thread'i o çekirdeğe bağlıyoruz
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
    
    LOGI("[Core Unclogger]: İşçi Çekirdek #%d üzerinde kilitlendi, limitör kırılıyor! 🚀", core_id);

    // 2. Çekirdeği uyutmamak ve frekansı en tepede tutmak için mikro döngü bindiriyoruz
    // (Arayüzü kitlememesi için bu işlem sadece 1.5 saniye sürecek, marş basma anı!)
    auto start_time = std::chrono::high_resolution_clock::now();
    double dummy = 3.14;
    
    while (true) {
        dummy = dummy * 1.00001; // Floating point ünitesini meşgul et
        
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
        
        if (elapsed > 1500) { // 1.5 saniye sonra işçi görevini tamamlar, frekans tavan yapmıştır bir kere!
            break;
        }
    }
    
    LOGI("[Core Unclogger]: Çekirdek #%d serbest bırakıldı, hat temiz.", core_id);
}

// Ana motorun (native-lib.cpp) çağıracağı o meşhur limitör iptal şalteri
extern "C" void start_core_unclogging() {
    LOGI("[Core Unclogger]: Limitör İptal Şalteri İndirildi! Tüm çekirdekler ayağa dikiliyor...");

    // Sistemdeki toplam çekirdek sayısını öğreniyoruz (Örn: 8 çekirdek)
    int total_cores = sysconf(_SC_NPROCESSORS_CONF);
    std::vector<std::thread> workers;

    // İlk 2 çekirdek genelde uyuşuk tasarruf çekirdekleridir, biz performans çekirdeklerini (büyük abileri) uyandırıyoruz
    for (int i = 2; i < total_cores; ++i) {
        workers.push_back(std::thread(clogger_worker, i));
    }

    // İşçilerin işini bitirmesini bekleyip ana hatta bağlıyoruz (Arayüz kilitlenmez çünkü asenkron)
    for (auto& t : workers) {
        if (t.joinable()) {
            t.detach(); // Arka planda bağımsız gazlasınlar usta, ana motoru beklemesinler
        }
    }
}

