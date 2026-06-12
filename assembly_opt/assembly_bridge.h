#ifndef ASSEMBLY_BRIDGE_H
#define ASSEMBLY_BRIDGE_H

#include <cstdint>

// C++ derleyicisine diyoruz ki: "Usta bunlara dokunma, bunlar dışarıdan gelen saf çelik Assembly kodlarıdır!"
extern "C" {
    // Android için NEON grafik hızlandırıcısı
    void android_neon_fast_blur(uint32_t* pixelData, uint64_t pixelCount);
    
    // Apple için donanımsal siber doğrulama zırhı (1: Temiz, 0: Hileli)
    int64_t apple_arm64_secure_verify(uint64_t* memoryAddress, uint64_t secureKey);
}

#endif

