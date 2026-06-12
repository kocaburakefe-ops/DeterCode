#ifndef ASSEMBLY_BRIDGE_H
#define ASSEMBLY_BRIDGE_H

#include <cstdint>

extern "C" {
    // 🤖 Android NEON Grafik Bulanıklaştırma (Mevcut)
    void android_neon_fast_blur(uint32_t* pixelData, uint64_t pixelCount);
    
    // 🍏 Apple Silicon Siber Doğrulama Zırhı (Mevcut)
    int64_t apple_arm64_secure_verify(uint64_t* memoryAddress, uint64_t secureKey);
    
    // 🔥 1. SÜTUN: Ultra Hızlı Donanımsal 4x4 Matris Çarpımı (YENİ)
    // float* türünde 16'şar elemanlı 3 adet diziyi işlemci düzeyinde çarpıştırır.
    void arm64_neon_matrix_multiply(const float* matrixA, const float* matrixB, float* matrixResult);
}

#endif
