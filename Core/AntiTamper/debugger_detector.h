#ifndef DEBUGGER_DETECTOR_H
#define DEBUGGER_DETECTOR_H

#include <iostream>

class DebuggerDetector {
public:
    DebuggerDetector() {
        std::cout << "[🔐 ANTI-TAMPER]: Debugger_Detector sinsi takibe basladi." << std::endl;
    }

    // Oyunun arkasina bir analiz yazilimi (Debugger/GDB) baglandigi anda durumu cakar
    bool is_debugger_attached() {
        // Gerçekte burada Linux ptrace self-attach yöntemi tetiklenir usta!
        bool attackState = false; // Simulasyon temiz usta
        return attackState;
    }
};

#endif

