#include <iostream>
#include <sys/mman.h>

void allocate_jit_space() {
    // Hem yazılabilir hem çalıştırılabilir bellek sayfası aç (PROT_READ | PROT_WRITE | PROT_EXEC)
    // Apple normalde buna izin vermez, özel bayraklarla etrafından dolaşıyoruz.
    void* jit_ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (jit_ptr != MAP_FAILED) {
        std::cout << "[DeterCode::JIT] Dinamik kod çalıştırma alanı belleğe haritalandı: " << jit_ptr << std::endl;
    }
}

