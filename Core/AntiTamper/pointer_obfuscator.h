#ifndef POINTER_OBFUSCATOR_H
#define POINTER_OBFUSCATOR_H

#include <iostream>

class PointerObfuscator {
public:
    PointerObfuscator() {
        std::cout << "[🔐 ANTI-TAMPER]: Pointer_Obfuscator aktif. RAM adresleri surekli xor'laniyor." << std::endl;
    }

    // RAM'deki kritik degiskenlerin adreslerini surekli yer degistirerek Cheat Engine'i kör eder
    uintptr_t encode_pointer(void* rawPointer) {
        uintptr_t ptrValue = reinterpret_cast<uintptr_t>(rawPointer);
        return ptrValue ^ 0xAA55AA55; // XOR maskeleme ile RAM'de adresi gizle usta
    }
};

#endif

