#include <iostream>
#include <string>
#include <sstream>
#include "bellek.hpp"

// matematik.cpp içindeki fonksiyonu buraya köprü olarak çağırıyoruz
void hesapla(std::stringstream& ss);

void komutIsle(std::string komut, std::stringstream& ss) {
    if (komut == "LOG") {
        std::string arguman;
        ss >> arguman;

        if (bellek.find(arguman) != bellek.end()) {
            std::cout << "[DeterCode LOG]: " << arguman << " = " << bellek[arguman] << std::endl;
        } else {
            std::string geriKalan;
            std::getline(ss, geriKalan);
            std::cout << "[DeterCode LOG]: " << arguman << geriKalan << std::endl;
        }
    }
    else if (komut == "SET") {
        std::string degisken, esittir, deger;
        ss >> degisken >> esittir >> deger;
        try {
            bellek[degisken] = std::stoi(deger);
            std::cout << "[DeterCode SET]: " << degisken << " = " << deger << " olarak hafizalandi." << std::endl;
        } catch (...) {
            std::cout << "[HATA]: Sayisal deger donusturulemedi." << std::endl;
        }
    }
    else if (komut == "CALC") {
        hesapla(ss); // Hesaplama işini uzmanına, yani matematik.cpp'ye devrediyoruz
    }
    else {
        std::cout << "[HATA]: Bilinmeyen komut -> " << komut << std::endl;
    }
}

void runDeterCode(std::string kodSatiri) {
    if (kodSatiri.empty() || kodSatiri[0] == '#') return;
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut;
    komutIsle(komut, ss);
}

