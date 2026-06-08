#ifndef BELLEK_HPP
#define BELLEK_HPP

#include <map>
#include <string>

// Global bellek haritamızı tanımlıyoruz
extern std::map<std::string, int> bellek;

// Hafızadan güvenli değer okuma fonksiyonu
inline int degerGetir(std::string arg) {
    try {
        if (bellek.find(arg) != bellek.end()) {
            return bellek[arg];
        }
        return std::stoi(arg); // Hafızada yoksa düz sayıdır (Örn: 30)
    } catch (...) {
        return 0; // Hatalı durumda emniyet kilidi
    }
}

#endif
#ifndef BELLEK_HPP
#define BELLEK_HPP

#include <map>
#include <string>

// Global bellek haritamızı tanımlıyoruz
extern std::map<std::string, int> bellek;

// Hafızadan güvenli değer okuma fonksiyonu
inline int degerGetir(std::string arg) {
    try {
        if (bellek.find(arg) != bellek.end()) {
            return bellek[arg];
        }
        return std::stoi(arg); // Hafızada yoksa düz sayıdır (Örn: 30)
    } catch (...) {
        return 0; // Hatalı durumda emniyet kilidi
    }
}

#endif

