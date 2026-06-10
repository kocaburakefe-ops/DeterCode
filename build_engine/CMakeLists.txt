cmake_minimum_required(VERSION 3.10)
project(DeterEngine)

# C++ standardını belirliyoruz
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tüm odaları (klasörleri) projeye dahil ediyoruz
include_directories(
    ../core_shared
    ../detercode_asm
    ../detercode_automotive
)

# Kaynak kod dosyalarımızı topluyoruz
set(SOURCES
    ../core_shared/core_unclogger.cpp
    ../core_shared/thermal_bypass.cpp
    ../detercode_automotive/can_bus_sniffer.cpp
    ../main.cpp # Buraya ana başlatıcıyı koyacağız
)

# Assembly dosyalarını ekliyoruz
set(ASM_SOURCES ../detercode_asm/asm_neon_booster.S)

# Motoru (Executable) oluşturuyoruz
add_executable(DeterEngine ${SOURCES} ${ASM_SOURCES})

message(STATUS "DeterEngine derleme haritası başarıyla yüklendi, usta!")

