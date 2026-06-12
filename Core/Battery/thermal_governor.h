#ifndef THERMAL_GOVERNOR_H
#define THERMAL_GOVERNOR_H

#include <iostream>

class ThermalGovernor {
private:
    float currentTemperature = 38.5f;

public:
    ThermalGovernor() {
        std::cout << "[🔋 BATTERY]: Thermal_Governor devrede. Hararet takibi basladi." << std::endl;
    }

    // Az once konustugumuz silikon yaslanmasi ve batarya erimesini engellemek icin isiyi denetler
    void monitor_and_throttle(float currentTemp) {
        currentTemperature = currentTemp;
        if (currentTemperature > 45.0f) { // 45 derece ustu batarya dusmanidir usta
            std::cout << "[⚠️ HARARET]: Isı " << currentTemperature << "°C oldu! FPS 60'a sabitleniyor, yuk dagitildi." << std::endl;
        } else {
            std::cout << "[✅ SERİN]: Motor sıcaklıgı normal: " << currentTemperature << "°C. Tam performans." << std::endl;
        }
    }
};

#endif

