#ifndef HARDWARE_TOKEN_CHECK_H
#define HARDWARE_TOKEN_CHECK_H

#include <iostream>
#include <string>

class HardwareTokenCheck {
public:
    HardwareTokenCheck() {
        std::cout << "[🔐 ANTI-TAMPER]: Hardware_Token_Check devrede. Donanim muhru aktif." << std::endl;
    }

    // Kayit dosyalarini acarken cihazin kendi CPU ID'sini kullanir; save dosyasinin baska telefona kopyalanmasini engeller
    bool verify_device_token(const std::string& saveToken, const std::string& currentCPUID) {
        if (saveToken != currentCPUID + "_MÜHÜR") {
            std::cout << "[🚨 SECURITY VIOLATION]: Calinti veya kopyalanmis save dosyasi algilandi!" << std::endl;
            return false; // Save dosyasini imha et usta!
        }
        return true;
    }
};

#endif

