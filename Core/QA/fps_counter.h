#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <iostream>

class FPSCounter {
public:
    FPSCounter() {
        std::cout << "[📊 QA-FPS]: FPS_Counter aktif. Donanim anlik izleniyor." << std::endl;
    }

    // Gecikmeleri ve kare surelerini milisaniye seviyesinde ekranda gosteren panel
    void log_frame_time(float deltaMilli) {
        if (deltaMilli > 16.67f) { // 60 FPS altina duserse usta sinyal çakar!
            std::cout << "[⚠️ PERFORMANCE DROP]: Kare suresi sasti: " << deltaMilli << " ms!" << std::endl;
        }
    }
};

#endif

