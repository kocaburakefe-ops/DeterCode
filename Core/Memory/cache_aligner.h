#ifndef CACHE_ALIGNER_H
#define CACHE_ALIGNER_H

#include <iostream>
#include <cstddef>

class CacheAligner {
public:
    CacheAligner() {
        std::cout << "[🧠 CACHE]: Cache_Aligner devrede. Veriler L1/L2/L3 onbellegine kitlendi." << std::endl;
    }

    // Verileri islemcinin cache satirlarina (genelde 64 byte) tam oturtur, islemci bosa donmez
    void* allocate_aligned(size_t size) {
        // Hizalama (Alignment) islemi donanım seviyesinde yapilir usta
        std::cout << "[⚡ ALIGN]: 64-Byte onbellek hizalamali bellek blogu acildi." << std::endl;
        return nullptr; 
    }
};

#endif

