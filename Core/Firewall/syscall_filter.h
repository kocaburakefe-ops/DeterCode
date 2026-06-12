#ifndef SYSCALL_FILTER_H
#define SYSCALL_FILTER_H

#include <iostream>
#include "../Diagnostics/blackbox.h"

class SyscallFilter {
private:
    BlackBox& fwLogger;

public:
    SyscallFilter(BlackBox& logger) : fwLogger(logger) {
        std::cout << "[🛡️ FIREWALL]: Syscall_Filter aktif. Sistem cagrilari denetleniyor." << std::endl;
    }

    // Motorun telefona gonderdigi sistem cagrilarini (Syscall) inceler, araya sızan sahte emirleri keser
    void filter_kernel_calls(int syscallID) {
        // Linux/Android seccomp benzeri ham donanim filtresi simulasyonu usta
        if (syscallID == 0xBAD) { // Sahte/Z zararli çağrı saptandigi an
            fwLogger.record(__FILE__, __LINE__, "CRITICAL", "ZARARLI SYSCALL ENGELLENDİ ID: " + std::to_string(syscallID));
            std::cout << "[❌ BLOCK]: Kernel seviyesinde yetkisiz erisim istegi reddedildi!" << std::endl;
        }
    }
};

#endif

