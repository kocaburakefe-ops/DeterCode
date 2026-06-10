cmake_minimum_required(VERSION 3.22.1)

# Projemizin C++ motoruna isim veriyoruz
project("detercode_native")

# Bizim yazdığımız native-lib.cpp dosyasını bir kütüphane olarak derlemesini söylüyoruz

add_library(
    detercode_native
    SHARED
    
    # 1. Ana Giriş Kapısı
    native-lib.cpp
    
    # 2. 5. Dilin Müstakil Odası (Assembly)
    asm_core/arm64_injector.S
    
    # 3. 1. ÖZELLİK: Çekirdek Limitör İptal Odası (YENİ EKLEME!)
    core_unclogger.cpp
)

# Android'in kendi sistem log kütüphanesini bağlıyoruz ki C++ içinden log basabilelim
find_library(
        log-lib
        log)

target_link_libraries(
        detercode_native
        ${log-lib})
        

add_library(
    detercode_native
    SHARED
    
    # Mevcut ana motorlar
    native-lib.cpp
    core_unclogger.cpp
    
    # YENİ EKLEDİĞİN ODALAR (ALTA GELECEKLER USTA)
    thermal_bypass.cpp
    ram_shifter.cpp
)

add_library(
    detercode_native
    SHARED
    
    # Eski canavarlar yerinde sabit kalıyor usta:
    native-lib.cpp
    core_unclogger.cpp
    thermal_bypass.cpp
    ram_shifter.cpp
    nice_override.cpp
    
    # 5. VİTESİ SADECE EN ALTA EKLEYECEKSİN:
    asm_neon_booster.cpp
)
