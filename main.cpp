#include <iostream>
#include "core_unclogger.h"
#include "can_bus_sniffer.h"
#include "thermal_bypass.h"

int main() {
    // 1. Karşılama ve Kontrol
    std::cout << "--- DeterEngine Başlatılıyor ---" << std::endl;
    
    // 2. Modüllerin Çağrılması (Namespace yapısına uygun)
    // Eğer modülleri DeterEngine:: namespace'ine aldıysan böyle çağır:
    
    try {
        std::cout << "[System]: Motor limitleri kaldırılıyor..." << std::endl;
        DeterEngine::Core::core_unclog_limits();
        
        std::cout << "[System]: Termal koruma aktif ediliyor..." << std::endl;
        DeterEngine::Thermal::manage_thermal_limits(true);
        
        std::cout << "[System]: CAN Bus hattı dinlenmeye başlandı..." << std::endl;
        DeterEngine::CAN::start_can_bus_sniffing();
        
        std::cout << "\n[DeterEngine]: Sistem Stabil, Gazlamaya Hazırız! 🚀" << std::endl;
    } 
    catch (...) {
        std::cerr << "[CRITICAL]: Başlatma sırasında hata oluştu!" << std::endl;
        return -1;
    }
    
    return 0;
}

