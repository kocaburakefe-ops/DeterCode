#ifndef REPLAY_DEFENDER_H
#define REPLAY_DEFENDER_H

#include <iostream>

class ReplayDefender {
public:
    ReplayDefender() {
        std::cout << "[🛡️ NET-FIREWALL]: Replay_Defender aktif. Zaman damgasi kontrolu basladi." << std::endl;
    }

    // Ag paketlerinin kopyalanip tekrar sisteme firlatilmasini (hileli nitro basma vb.) engeller
    bool validate_packet_timestamp(long packetTime, long currentTime) {
        if (currentTime - packetTime > 2000) { // 2 saniyeden eski paket gelirse hiledir usta
            std::cout << "[❌ REPLAY ATTACK]: Zaman asimina ugramis kopya paket engellendi!" << std::endl;
            return false;
        }
        return true;
    }
};

#endif

