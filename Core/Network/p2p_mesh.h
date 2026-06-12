#ifndef P2P_MESH_H
#define P2P_MESH_H

#include <iostream>
#include <string>

class P2PMesh {
public:
    P2PMesh() {
        std::cout << "[🌐 NETWORK]: P2P_Mesh aktif. Sunucusuz dogrudan baglantı hatti kuruldu." << std::endl;
    }

    // Merkezi sunucuya yuk bindirmemek icin yan yana yarisan arabalarin verisini direkt birbirine aktarir
    void broadcast_position_to_peer(const std::string& peerIP, float x, float y) {
        // Peer-to-Peer veri paketi fırlatma simulasyonu usta
        std::cout << "[📡 P2P SEND]: " << peerIP << " adresindeki rakibe anlık koordinat uçuruldu: X:" << x << " Y:" << y << std::endl;
    }
};

#endif

