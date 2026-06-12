#ifndef PACKET_COMPRESSOR_H
#define PACKET_COMPRESSOR_H
#include <iostream>
#include <string>

class PacketCompressor {
public:
    PacketCompressor() { std::cout << "[🌐 NETWORK]: Packet_Compressor devrede. Paketler presleniyor." << std::endl; }
    std::string compress_packet(const std::string& rawData) {
        std::cout << "[🤐 COMPRESS]: Ag paketi bayt seviyesinde preslendi. Kotadan tasarruf." << std::endl;
        return "COMPRESSED_" + rawData;
    }
};
#endif

