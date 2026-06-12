#ifndef ASSEMBLY_BRIDGE_H
#define ASSEMBLY_BRIDGE_H

#include <cstdint>

extern "C" {
    // 🤖 Android NEON Grafik Bulanıklaştırma
    void android_neon_fast_blur(uint32_t* pixelData, uint64_t pixelCount);
    
    // 🍏 Apple Silicon Siber Doğrulama Zırhı
    int64_t apple_arm64_secure_verify(uint64_t* memoryAddress, uint64_t secureKey);
    
    // 🔥 1. SÜTUN: Ultra Hızlı Donanımsal 4x4 Matris Çarpımı
    void arm64_neon_matrix_multiply(const float* matrixA, const float* matrixB, float* matrixResult);
    
    // 🛡️ 2. SÜTUN: Apple Silicon Donanımsal AES Şifreleme
    void apple_hardware_aes_encrypt(const uint8_t* plaintext, const uint8_t* key, uint8_t* ciphertext);

    // ⚔️ 3. SÜTUN: ARM64 Çekirdek Seviyesi Donanımsal Anti-Debug
    void arm64_anti_ptrace_sys();

    // 🚀 4. SÜTUN: Donanımsal Hızlı Vektör Fizik Hesaplayıcı (YENİ)
    // 4 elemanlı iki float dizisini işlemci seviyesinde tek turda çarpar.
    void arm64_fast_vector_multiply(const float* vectorA, const float* vectorB, float* vectorResult);
}

#endif
