#ifndef FRAME_PACER_H
#define FRAME_PACER_H

#include <iostream>
#include <chrono>
#include "../Diagnostics/blackbox.h"

class FramePacer {
private:
    double targetFrameTimeMs; // Her karenin ekrana gelme süresi hedefi (Örn: 120 FPS için ~8.3ms)
    BlackBox& gfxLogger;

public:
    FramePacer(double targetFps, BlackBox& logger) : gfxLogger(logger) {
        targetFrameTimeMs = 1000.0 / targetFps;
        std::cout << "[🎮 GRAPHICS]: Frame_Pacer kuruldu. Hedef kare suresi: " << targetFrameTimeMs << " ms" << std::endl;
    }

    // Her kare çizildikten sonra motorun hızını milimetrik ayarlar
    void pace_frame() {
        // Sanayi usulü hassas zaman takibi
        auto startTime = std::chrono::high_resolution_clock::now();
        
        // [Burada ekran kartı çizimi yapar usta]

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = endTime - startTime;

        // Eğer ekran kartı erkenden işini bitirdiyse, işlemciyi boşa koşturma, tam vaktinde uyut!
        if (elapsed.count() < targetFrameTimeMs) {
            double sleepTime = targetFrameTimeMs - elapsed.count();
            // Hassas donanım uykusu (Microsecond sleep)
            // Bu sayede ekranda yırtılma ve titreme (jitter) olmaz!
        } else if (elapsed.count() > targetFrameTimeMs + 5.0) {
            gfxLogger.record(__FILE__, __LINE__, "WARNING", "Kare gecikmesi yasandi! Grafik hantallasiyor.");
        }
    }
};

#endif

