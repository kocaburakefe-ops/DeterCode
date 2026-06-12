#include <iostream>
#include <thread>

// 🛠️ 1. KATMAN: DIAGNOSTICS & SYSTEM & POWER
#include "Core/Diagnostics/blackbox.h"
#include "Core/Power/nos_trigger.h"
#include "Core/System/kernel_bridge.h"

// 🛠️ 2. KATMAN: GRAPHICS & INPUT & CONCURRENCY
#include "Core/Graphics/frame_pacer.h"
#include "Core/Input/event_dispatcher.h"
#include "Core/Concurrency/thread_worker.h"

// 🛠️ 3. KATMAN: AUDIO & RESOURCES & PHYSICS & MATH (YENİ EKİP)
#include "Core/Audio/audio_mixer.h"
#include "Core/Resources/asset_bundler.h"
#include "Core/Physics/physics_solver.h"
#include "Core/Math/deter_math.h"

// Arka planda çalışacak örnek görev (Thread_Worker için)
void background_asset_stream() {
    std::cout << "[🧵 THREAD-TASK]: Arka planda yuksek boyutlu dokular isleniyor..." << std::endl;
}

int main() {
    std::cout << "==========================================================" << std::endl;
    std::cout << "👑 DETERENGINE V1.0 - 20 OZELLIKLI SAFKAN MOTOR AYAKTA 👑" << std::endl;
    std::cout << "==========================================================" << std::endl;

    // 🛡️ ADIM 1: Zırhlı Kara Kutuyu ve Temel Altyapıyı Başlat
    BlackBox blackbox;
    KernelBridge kernel(blackbox);
    ThreadWorker worker(blackbox);

    // 📦 ADIM 2: Yeni Canavarları Devreye Al (Ses, Fizik, Kaynak Yönetimi)
    AssetBundler bundler(blackbox);
    AudioMixer audio(blackbox);
    PhysicsSolver physics(blackbox);
    DeterMath dMath; // Hızlı matematik sınıfımız statiktir, hazırdır.

    // 🏎️ ADIM 3: Kaynak Yükleme ve Çoklu Çekirdek Simülasyonu (16. ve 18. Özellik)
    bundler.stream_asset_to_ram("BMW_E36_3D_Model.asset");
    worker.deploy_task_to_background(background_asset_stream);

    // 🕹️ ADIM 4: Gecikmesiz Giriş ve Ses Patlaması (15. ve 17. Özellik)
    input.push_hardware_event("TOUCH_DOWN", 500, 1000);
    audio.play_sound_instant("E36_M50_EGZOZ_SESI.wav");

    // 🖥️ ADIM 5: Kernel Seviyesi Donanım Bağlantısı (13. Özellik)
    kernel.engage_direct_hardware_access(true);
    kernel.optimize_cpu_affinity(0); // 0. çekirdeğe oyunu kitledik

    // 🚀 ADIM 6: NOS Tetikleme ve Hızlı Matematik (12. ve 20. Özellik)
    NOSTrigger nos(blackbox);
    nos.trigger_nitro(true);

    // Efsane hızlı karekök kodumuzu test edelim (Farkı gör usta!)
    float invSqrtSample = DeterMath::fast_inverse_sqrt(16.0f);
    std::cout << "[🧮 MATH-TEST]: Hizli karekok sonucu (16 icin): " << invSqrtSample << std::endl;

    // ⏱️ ADIM 7: Grafik Akıcılığı ve Fizik Hesapları (14. ve 19. Özellik)
    FramePacer pacer(nos.get_current_fps_target(), blackbox);
    pacer.pace_frame();
    physics.solve_collisions(120.5f, 440.2f);

    // 🔥 ADIM 8: PANİK ŞALTERİ VE GÜVENLİK SİMÜLASYONU
    std::cout << "\n⚠️ [UYARI]: Otobanda hiz limiti asildi, yuksek islemci yuklenmesi..." << std::endl;
    int currentCpuTemp = 89; // Sıcaklık kritik sınıra vurdu!
    
    // Sistem 85 dereceyi geçtiği için kara kutu anında devreye girecek!
    nos.check_system_stability(currentCpuTemp);

    // Temizlik (Kara kutu sistemi kapatmazsa buraya ulaşır)
    worker.synchronize_workers();
    return 0;
}
