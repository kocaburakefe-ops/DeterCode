// =========================================================================
// 🏛️ SÜTUN 2: DONANIMSAL KRİPTO ZIRH - APPLE AES HARDWARE (ARM64)
// =========================================================================
.global apple_hardware_aes_encrypt
.align 4

apple_hardware_aes_encrypt:
    // x0: Şifrelenecek 16-byte'lık verinin RAM adresi (Plaintext)
    // x1: Şifreleme anahtarının RAM adresi (128-bit Cipher Key)
    // x2: Şifrelenmiş sonucun yazılacağı RAM adresi (Output)

    // 1. Veriyi ve Anahtarı işlemci odasına (Vektör Register'lara) çekiyoruz
    ld1         {v0.16b}, [x0]          // 16-byte veriyi v0 içine al
    ld1         {v1.16b}, [x1]          // 16-byte anahtarı v1 içine al

    // 2. İşlemcinin içindeki gizli kripto motorunu ateşliyoruz!
    aese        v0.16b, v1.16b          // Donanımsal AES Tek Tur Şifreleme (Mermi Hızı)
    aesmc       v0.16b, v0.16b          // Donanımsal MixColumns Karıştırma Döngüsü

    // Son bir cıvata: Anahtarla son bir XOR çakıştırıp işi bitiriyoruz
    eor         v0.16b, v0.16b, v1.16b

    // 3. Çelikten çıkan şifreli veriyi doğrudan çıktı adresine fırlat!
    st1         {v0.16b}, [x2]

    ret                                 // Marşı kapat, C++'a güvenli rapor ver.

