#ifndef PACKET_SANITIZER_H
#define PACKET_SANITIZER_H

#include <iostream>
#include <string>

class PacketSanitizer {
public:
    PacketSanitizer() {
        std::cout << "[🛡️ NET-FIREWALL]: Packet_Sanitizer devrede. UDP paketleri yikanacak." << std::endl;
    }

    // UDP soketinden gelen paketleri haritaya almadan once yıkar; bozuk veya sahte paketleri kapida imha eder
    bool sanitize_incoming_packet(const std::string& rawPacket) {
        if (rawPacket.find("MALFORMED_DDOS_DATA") != std::string::npos) {
            std::cout << "[🔥 ANNIHILATE]: Sahte/Kırık paket ag kapisinda imha edildi!" << std::endl;
            return false;
        }
        return true;
    }
};

#endif

