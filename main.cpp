#include <iostream>
#include "core_unclogger.h"
#include "can_bus_sniffer.h"
#include "thermal_bypass.h"
#include "asm_linker.h" // Assembly köprüsünü de buraya bağladık

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "--- DeterEngine Marşa Basılıyor ---" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 1. Motoru optimize et
    std::cout << "[SYSTEM]: Motor limitleri kaldırılıyor..." << std::endl;
    core_unclog_limits();
    
    // 2. Isınmayı yönet
    std::cout << "[SYSTEM]: Termal bypass aktif ediliyor..." << std::endl;
    manage_thermal_limits(true);
    
    // 3. Otomotiv hattını dinle
    std::cout << "[SYSTEM]: CAN Bus hattı dinleniyor..." << std::endl;
    start_can_bus_sniffing();
    
    // 4. Assembly Süper Güç Testi
    std::cout << "[ASSEMBLY]: Düşük seviye işlemci testi yapılıyor..." << std::endl;
    long test_sonucu = fast_multiply_asm(10, 20);
    std::cout << "[ASSEMBLY]: 10 x 20 İşlem Sonucu: " << test_sonucu << " (İşlemci saniyede hesapladı!)" << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "--- Sistem Stabil, Gazlamaya Hazırız! ---" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}

