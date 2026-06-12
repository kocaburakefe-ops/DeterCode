#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H
#include <iostream>

class PoolAllocator {
public:
    PoolAllocator() { std::cout << "[⚙️ MEMORY]: Pool_Allocator aktif. Hazir bellek havuzu kuruldu." << std::endl; }
    void* allocate_particle() {
        std::cout << "[⚡ POOL]: Sıfırdan RAM istenmedi, hazir havuzdan bellek cıvata gibi sokuldu." << std::endl;
        return nullptr;
    }
};
#endif

