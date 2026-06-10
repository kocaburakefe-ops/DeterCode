#include "data_bridge.h"
#include <iostream>

namespace DeterEngine {
    namespace Bridge {
        void send_message(const std::string& sender, const std::string& message) {
            std::cout << "[Bridge]: " << sender << " -> [Duyuru]: " << message << std::endl;
        }

        void broadcast_status() {
            std::cout << "[Bridge]: Tüm sistem durumu senkronize edildi." << std::endl;
        }
    }
}
