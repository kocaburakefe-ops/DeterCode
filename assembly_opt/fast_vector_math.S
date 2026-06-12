// =========================================================================
// 🏛️ SÜTUN 4: SAF MATEMATİK VE HIZLI VEKTÖR MOTORU (ARM64 FLOATING POINT)
// =========================================================================
.global arm64_fast_vector_multiply
.align 4

arm64_fast_vector_multiply:
    // x0: Birinci 4'lü fizik vektörünün RAM adresi (Float dizisi: X, Y, Z, W)
    // x1: İkinci 4'lü fizik vektörünün RAM adresi (Float dizisi katsayıları)
    // x2: Sonucun yazılacağı çıktı RAM adresi

    // 1. Verileri doğrudan işlemcinin 128-bitlik matkap uçlarına (Vektör Register) yüklüyoruz
    ld1         {v0.4s}, [x0]           // 4 tane float sayıyı tek seferde v0'a çek
    ld1         {v1.4s}, [x1]           // 4 tane katsayıyı tek seferde v1'a çek

    // 2. İşlemciye emri çakıyoruz: 4 sayıyı aynı anda birbiriyle çarp!
    fmul        v2.4s, v0.4s, v1.4s     // Donanımsal Vektör Çarpımı (Hararet sıfır!)

    // 3. Çelikten çıkan fizik sonuçlarını doğrudan çıktı adresine fırlat!
    st1         {v2.4s}, [x2]

    ret                                 // Krank milini durdur, C++ dünyasına rapor ver.

