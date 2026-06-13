#include <iostream>
#include <vector>

class PacketFilter {
public:
    void inspectPacket(std::vector<uint8_t> packet) {
        // Gelen ağ paketinin başlıklarını (header) oku
        if (packet.size() > 20 && packet[0] == 0x45) { // IPv4 kontrolü
            std::cout << "[DeterCode::Network] IP Paketi yakalandı, şifreleme maskesi uygulanıyor." << std::endl;
        }
    }
};

