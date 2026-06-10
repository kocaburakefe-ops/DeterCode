#include <iostream>
#include "core_unclogger.h"
#include "can_bus_sniffer.h"
#include "thermal_bypass.h"

int main() {
    std::cout << "--- DeterEngine Marşa Basılıyor ---" << std::endl;
    
    // 1. Motoru optimize et
    core_unclog_limits();
    
    // 2. Isınmayı yönet
    manage_thermal_limits(true);
    
    // 3. Otomotiv hattını dinle
    start_can_bus_sniffing();
    
    std::cout << "--- Sistem Stabil, Gazlamaya Hazırız! ---" << std::endl;
    
    return 0;
}

