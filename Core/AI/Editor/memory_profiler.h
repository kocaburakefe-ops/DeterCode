#ifndef MEMORY_PROFILER_H
#define MEMORY_PROFILER_H

#include <iostream>
#include "../Diagnostics/blackbox.h"

class MemoryProfiler {
private:
    BlackBox& profilerLogger;

public:
    MemoryProfiler(BlackBox& logger) : profilerLogger(logger) {
        std::cout << "[⚙️ PROFILER]: Memory_Profiler dedektifi RAM kacaklarini izlemek icin uyandi!" << std::endl;
    }

    // Motor calisirken hangi modülün ne kadar RAM yedigini saniye saniye denetler
    void profile_allocated_bytes(size_t bytes) {
        if (bytes > 1024 * 1024 * 512) { // Oyun 512 MB bellek sınırını gecerse uyar!
            profilerLogger.record(__FILE__, __LINE__, "WARNING", "Motor yuksek RAM tuketim modunda! Temizlik gerekiyor.");
        }
    }
};

#endif

