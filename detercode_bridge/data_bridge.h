#ifndef DATA_BRIDGE_H
#define DATA_BRIDGE_H

#include <string>

namespace DeterEngine {
    namespace Bridge {
        // Tüm modüller arası mesajlaşma merkezi
        void send_message(const std::string& sender, const std::string& message);
        void broadcast_status();
    }
}

#endif

