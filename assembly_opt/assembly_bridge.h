#ifndef ASSEMBLY_BRIDGE_H
#define ASSEMBLY_BRIDGE_H

#include <cstdint>

extern "C" {
    // 🤖 Android NEON Grafik Bulanıklaştırma (Mevcut)
    void android_neon_fast_blur(uint32_t* pixelData, uint64_t pixelCount);
    
    // 🍏 Apple Silicon Siber Doğrulama Zırhı (Mevcut)
    int64_t apple_arm64_secure_verify(uint64_t* memoryAddress, uint64_t secureKey);
    
    // 🔥 1. SÜTUN: Ultra Hızlı Donanımsal 4x4 Matris Çarpımı (Mevcut)
    void arm64_neon_matrix_multiply(const float* matrixA, const float* matrixB, float* matrixResult);
    
    // 🛡️ 2. SÜTUN: Apple Silicon Donanımsal AES Şifreleme (YENİ)
    // 16-byte veriyi, 16-byte anahtar kullanarak donanım düzeyinde şifreler.
    void apple_hardware_aes_encrypt(const uint8_t* plaintext, const uint8_t* key, uint8_t* ciphertext);
}

#endif
