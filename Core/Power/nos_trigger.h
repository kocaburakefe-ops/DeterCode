#ifndef NOS_TRIGGER_H
#define NOS_TRIGGER_H

#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h" // Kara kutuyu buraya bağlıyoruz usta!

class NOSTrigger {
private:
    bool isNOSActive;
    double targetFps;
    BlackBox& engineLogger; // Olası bir patlamada suç mahallini kaydedecek şerit

public:
    // Motorun kara kutusunu buraya referans olarak bağlıyoruz ki gözü üzerimizde olsun
    NOSTrigger(BlackBox& logger) : isNOSActive(false), targetFps(60.0), engineLogger(logger) {
        std::cout << "[⚙️ POWER]: NOS_Trigger (Nitro Overclock System) hazir ve nazir!" << std::endl;
    }

    // 🔥 YAZILIMCININ OYUN İÇİNDEN TETİKLEYECEĞİ O MEŞHUR BUTON!
    void trigger_nitro(bool activate) {
        isNOSActive = activate;
        
        if (isNOSActive) {
            targetFps = 120.0; // İşlemci ve grafik döngüsünü 2 katına fırlat usta!
            std::cout << "\n🚀 [NOS ACTIVATED]: Islemci sinirlari zorluyor! Hedef 120 FPS! 🔥" << std::endl;
            
            // Kara kutuya o anı fısılda
            engineLogger.record(__FILE__, __LINE__, "INFO", "NOS Modu tetiklendi. Islemci yuksek performans moduna gecti.");
            
            // Burası sanayi usulü doğrudan donanımla konuşma yeri:
            // Gerçek projede burada Android Kernel'ına veya CPU frekans valflerine doğrudan sinyal gönderilir usta.
            
        } else {
            targetFps = 60.0; // Normal ekonomi moduna geri dön
            std::cout << "⏱️ [NOS DEACTIVATED]: Motor stabil moda gecti. Hedef 60 FPS." << std::endl;
            engineLogger.record(__FILE__, __LINE__, "INFO", "NOS Modu kapatildi. Sistem sakin.");
        }
    }

    // Motorun anlık performans durumunu kontrol eden fonksiyon
    void check_system_stability(int currentTemp) {
        if (isNOSActive && currentTemp > 85) { // Eğer NOS açıkken işlemci 85 dereceyi geçerse!
            // Gözünün yaşına bakma, panik şalterini indirip kara kutuyu açıyoruz!
            engineLogger.record(__FILE__, __LINE__, "CRITICAL", "DONANIM TEHLİKEDE: NOS acikken islemci sicakligi 85 dereceyi asti!");
        }
    }

    double get_current_fps_target() const {
        return targetFps;
    }
};

#endif
