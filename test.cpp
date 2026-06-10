#include <iostream>

// --- MOTOR FONKSİYONLARI ---
void core_unclog_limits() {
    std::cout << "[CORE]: Limitler iptal edildi." << std::endl;
}

void manage_thermal_limits(bool active) {
    std::cout << "[THERMAL]: Bypass aktif." << std::endl;
}

void start_can_bus_sniffing() {
    std::cout << "[CAN]: Hat dinleniyor." << std::endl;
}

// --- TELEFON İÇİN ANA GİRİŞ ---
int main() {
    std::cout << "DeterEngine Baslatiliyor..." << std::endl;
    
    core_unclog_limits();
    manage_thermal_limits(true);
    start_can_bus_sniffing();
    
    std::cout << "Sistem Aktif! 🚀" << std::endl;
    return 0;
}

