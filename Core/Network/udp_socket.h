#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h"

class UDPSocket {
private:
    int socketFd;
    BlackBox& netLogger;

public:
    UDPSocket(BlackBox& logger) : socketFd(-1), netLogger(logger) {
        std::cout << "[🌐 NETWORK]: UDP_Socket aktif. Sifir gecikmeli veri hatti acildi!" << std::endl;
    }

    // Yarista milisaniyelik ping olmasin diye paketleri hic bekletmeden havaya fırlatır
    void send_packet_instant(const std::string& packetData, const std::string& ipAddress) {
        // Sanayi usulü ham veri transferi simülasyonu
        // Gerçekte burada Linux/Android sys/socket.h baglantisi kurulur usta.
        if (packetData.empty()) {
            netLogger.record(__FILE__, __LINE__, "WARNING", "Bos ag paketi gonderilmeye calisildi!");
            return;
        }
        // Paket basildi!
    }
};

#endif
