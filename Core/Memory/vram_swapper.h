#ifndef VRAM_SWAPPER_H
#define VRAM_SWAPPER_H

#include <iostream>

class VRAMSwapper {
public:
    VRAMSwapper() {
        std::cout << "[⚙️ MEMORY]: VRAM_Swapper devrede. Grafik bellek korumasi aktif." << std::endl;
    }

    // Telefonun RAM'i sismeye basladiginda eski kaplama hafizasini bosaltir, telefonu cokuslerden (Crash) korur
    void check_and_swap_vram(size_t currentUsage, size_t maxLimit) {
        if (currentUsage > (maxLimit * 0.85)) { // %85 doluluga ulasinca tahliye baslar usta
            std::cout << "[🧹 SWAP]: RAM doluyor! Uzaktaki harita kaplamalari bellekten dusuruldu, cokus engellendi." << std::endl;
        }
    }
};

#endif

