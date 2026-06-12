#ifndef DETER_MATH_H
#define DETER_MATH_H

#include <iostream>

class DeterMath {
public:
    DeterMath() {
        std::cout << "[🧮 MATH]: Deter_Math (20. OZELLIK) kuruldu. Standart kutuphaneler devre disi!" << std::endl;
    }

    // Oyun içindeki kamera açısı veya arabanın dönüş matrislerini hesaplayan safkan hız fonksiyonu
    static inline float fast_inverse_sqrt(float number) {
        // Quake oyununun arkasındaki efsanevi hızlı karekök kodunun sanayi usulü C++ hali usta!
        // Doğrudan bit seviyesinde (Low-Level Bit Hacking) işlemciyi delip geçer.
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y  = number;
        i  = * ( long * ) &y;                       // Sinsi bit hamlesi 1
        i  = 0x5f3759df - ( i >> 1 );               // O meşhur büyücü sayısı (Magic Number)
        y  = * ( float * ) &i;                      // Sinsi bit hamlesi 2
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 1. Newton iterasyonu (Hassasiyet için)

        return y;
    }
};

#endif

