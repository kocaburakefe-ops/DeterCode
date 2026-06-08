// deter_lib.h
#ifndef DETER_LIB_H
#define DETER_LIB_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

// Bellek yapımızı kütüphaneye taşıyoruz
extern std::map<std::string, int> bellek;

// Komut işleyici fonksiyonumuz
void komutIsle(std::string komut, std::stringstream& ss) {
    if (komut == "LOG") {
        std::string mesaj;
        std::getline(ss, mesaj);
        std::cout << "[DeterCode LOG]: " << mesaj << std::endl;
    }
    else if (komut == "SET") {
        std::string degisken, esittir, deger;
        ss >> degisken >> esittir >> deger;
        bellek[degisken] = std::stoi(deger); // Belleğe kaydettik!
        std::cout << "[DeterCode SET]: " << degisken << " = " << deger << std::endl;
    }
    // Diğer komutlar buraya...
}

#endif

