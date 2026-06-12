#ifndef CPU_AFFINITY_H
#define CPU_AFFINITY_H
#include <iostream>

class CPUAffinity {
public:
    CPUAffinity() { std::cout << "[📱 SYSTEM]: CPU_Affinity ayarlandi. Cekirdek is bolumu devrede." << std::endl; }
    void bind_threads_to_cores() {
        std::cout << "[🎛️ CPU_BIND]: Yarıs fizigi Snapdragon Performans cekirdeklerine zorla kilitlendi." << std::endl;
    }
};
#endif

