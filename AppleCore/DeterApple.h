#ifndef DETER_APPLE_H
#define DETER_APPLE_H

#include <iostream>
#include <vector>
#include <cstdint>

class DeterApple {
public:
    DeterApple();
    ~DeterApple();

    // Elma işlemcisinin damarlarına sızma ve hafıza haritasını çıkarma
    bool bypassSandbox();
    bool secureMemoryRegions();
    void optimizeAppleSilicon();

private:
    bool isUnderDebugger();
    uint64_t getKernelBaseAddress();
    std::vector<uint8_t> assembly_patch_buffer;
};

#endif // DETER_APPLE_H

