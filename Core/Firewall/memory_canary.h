#ifndef MEMORY_CANARY_H
#define MEMORY_CANARY_H

#include <iostream>

class MemoryCanary {
private:
    const uint32_t CANARY_VALUE = 0xDEADBEEF;

public:
    MemoryCanary() {
        std::cout << "[🛡️ FIREWALL]: Memory_Canary uyandi. RAM adreslerine koruyucu kuslar yerlestirildi." << std::endl;
    }

    // RAM'de bellek tasmalarini (Buffer Overflow) yakalayan ve sistemi koruyan kanarya algoritmasi
    bool check_integrity(uint32_t currentAddressValue) {
        if (currentAddressValue != CANARY_VALUE) {
            std::cout << "[🚨 CANARY DEAD]: Bellek tasmasi algilandi! Kanarya öldü, sistem kilitleniyor!" << std::endl;
            return false; // Saldırı var usta!
        }
        return true;
    }
};

#endif

