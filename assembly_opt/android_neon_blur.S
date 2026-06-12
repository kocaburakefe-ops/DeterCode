// =========================================================================
// 🔥 DETERENGINE ASSEMBLY OPTIMIZATION - ANDROID NEON BLUR (ARM64)
// =========================================================================
.global android_neon_fast_blur
.align 4

android_neon_fast_blur:
    // x0: Grafik piksel dizisinin adresi (RAM)
    // x1: Piksel sayısı
    
    // İşlemciye emri veriyoruz: Her turda 4 tane 32-bit pikseli tek marşta işle!
.loop_neon:
    cmp         x1, #4                  // Kalan piksel 4'ten az mı?
    b.lt        .loop_scalar            // Az kaldıysa normal döngüye geç
    
    ld1         {v0.4s}, [x0]           // 4 pikseli (128-bit) tek seferde v0 işlemci odasına çek!
    
    // Burada o gizli grafik/parlaklık matematiğini işlemci çekirdeğinde uçuruyoruz
    shl         v1.4s, v0.4s, #1        // Pikselleri bit seviyesinde 1 sola kaydır (Mermi gibi çarpma)
    add         v1.4s, v1.4s, v0.4s     // Orijinal veriyle işlemci içinde topla
    
    st1         {v1.4s}, [x0], #16      // İşlenen 4 pikseli RAM'e geri fırlat, adresi 16 byte kaydır
    sub         x1, x1, #4              // Sayaçtan 4 düş
    b           .loop_neon              // Devam usta, silindirler dönsün!

.loop_scalar:
    cmp         x1, #0
    b.eq        .exit_neon
    ldr         w2, [x0]                // Tek kalan pikselleri klasik yöntemle erit
    lsl         w3, w2, #1
    add         w3, w3, w2
    str         w3, [x0], #4
    sub         x1, x1, #1
    b           .loop_scalar

.exit_neon:
    ret                                 // Marşı kapat, C++ dünyasına dön.

