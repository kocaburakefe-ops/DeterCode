// =========================================================================
// 🏛️ SÜTUN 1: ULTRA GRAFİK VE MATRİS MOTORU (ARM64 NEON PARALLEL)
// =========================================================================
.global arm64_neon_matrix_multiply
.align 4

arm64_neon_matrix_multiply:
    // x0: Birinci 4x4 Matrisin RAM adresi (A Matrisi - Float dizisi)
    // x1: İkinci 4x4 Matrisin RAM adresi (B Matrisi - Float dizisi)
    // x2: Sonucun yazılacağı RAM adresi (Result Matrisi)

    // 1. SATIRIN İŞLENMESİ (İşlemci odalarını yani Register'ları mermi gibi dolduruyoruz)
    ld1         {v0.4s, v1.4s, v2.4s, v3.4s}, [x0]    // A matrisinin tüm satırlarını v0-v3 arasına çek
    ld1         {v4.4s, v5.4s, v6.4s, v7.4s}, [x1]    // B matrisinin tüm satırlarını v4-v7 arasına çek

    // NEON Vektör işlemcisine emir veriliyor: Satır ve sütunları tek turda çarp ve topla!
    fmul        v16.4s, v4.4s, v0.s[0]
    fmla        v16.4s, v5.4s, v0.s[1]
    fmla        v16.4s, v6.4s, v0.s[2]
    fmla        v16.4s, v7.4s, v0.s[3]
    st1         {v16.4s}, [x2], #16                   // 1. Satır bitti, direkt RAM'e fırlat!

    // 2. SATIRIN İŞLENMESİ
    fmul        v17.4s, v4.4s, v1.s[0]
    fmla        v17.4s, v5.4s, v1.s[1]
    fmla        v17.4s, v6.4s, v1.s[2]
    fmla        v17.4s, v7.4s, v1.s[3]
    st1         {v17.4s}, [x2], #16                   // 2. Satır bitti, RAM'e fırlat!

    // 3. SATIRIN İŞLENMESİ
    fmul        v18.4s, v4.4s, v2.s[0]
    fmla        v18.4s, v5.4s, v2.s[1]
    fmla        v18.4s, v6.4s, v2.s[2]
    fmla        v18.4s, v7.4s, v2.s[3]
    st1         {v18.4s}, [x2], #16                   // 3. Satır bitti, RAM'e fırlat!

    // 4. SATIRIN İŞLENMESİ
    fmul        v19.4s, v4.4s, v3.s[0]
    fmla        v19.4s, v5.4s, v3.s[1]
    fmla        v19.4s, v6.4s, v3.s[2]
    fmla        v19.4s, v7.4s, v3.s[3]
    st1         {v19.4s}, [x2]                        // Son satır bitti, matris tamamlandı!

    ret                                               // Krank milini durdur, C++'a dön.

