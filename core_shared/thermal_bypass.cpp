#include "thermal_bypass.h"
#include <iostream>

void manage_thermal_limits(bool enable_bypass) {
    if (enable_bypass) {
        std::cout << "[CoreShared]: Termal limitler bypass edildi. Performans moduna geçiliyor!" << std::endl;
        // Burada işletim sistemi düzeyinde CPU governor ayarları (performance mode) tetiklenir
    } else {
        std::cout << "[CoreShared]: Termal güvenlik kalkanları aktif." << std::endl;
    }
}

float get_system_temp() {
    // Burada donanımın sensöründen gerçek veriyi okuruz
    return 45.5f; // Örnek sıcaklık
}

