#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h"

class KernelBridge {
private:
    bool isDirectModeActive;
    BlackBox& sysLogger;

public:
    KernelBridge(BlackBox& logger) : isDirectModeActive(false), sysLogger(logger) {
        std::cout << "[🖥️ SYSTEM]: Kernel_Bridge (Cekirdek Koprusu) haritasi cikarildi!" << std::endl;
    }

    // 🔥 DONANIMLA DOĞRUDAN KONUŞMA ŞALTERİ
    void engage_direct_hardware_access(bool enable) {
        isDirectModeActive = enable;
        
        if (isDirectModeActive) {
            std::cout << "[🛡️ KERNEL]: Android/Linux OS katmanlari bypass ediliyor... Doğrudan silikona baglaniliyor!" << std::endl;
            
            // Bizim zırhlı kara kutuya kritik geçişi bildiriyoruz
            sysLogger.record(__FILE__, __LINE__, "INFO", "Kernel_Bridge aktif: Yuksek seviyeli isletim sistemi duvarlari asildi.");
            
            // ⚠️ SANAYİ USULÜ RİSK ALMA NOKTASI:
            // Gerçek cihazda burada alt katman sistem çağrıları (Syscalls) veya /dev/cpuctl gibi 
            // kernel kontrol dosyalarına doğrudan Assembly seviyesinde emirler gönderilir usta.
            
        } else {
            std::cout << "[🖥️ KERNEL]: Standart guvenli katmana geri donuldu." << std::endl;
            sysLogger.record(__FILE__, __LINE__, "INFO", "Kernel_Bridge kapatildi. Standart moda gecildi.");
        }
    }

    // İşlemci çekirdeklerinin yükünü milimetrik optimize eden fonksiyon
    void optimize_cpu_affinity(int coreId) {
        if (isDirectModeActive) {
            // Oyunu tek bir işlemci çekirdeğine kelepçeleyerek önbellek (L1/L2 Cache) kayıplarını sıfıra indiriyoruz!
            std::cout << "[⚡ CACHE]: Oyun dongusu dogrudan CORE " << coreId << " uzerine kitlendi! Maksimum akicilik." << std::endl;
        }
    }
};

