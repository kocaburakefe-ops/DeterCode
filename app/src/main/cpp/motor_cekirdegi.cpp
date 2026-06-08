#include <iostream>
#include <string>
#include <sstream>
#include <fstream> // Dosya okumak için yeni kütüphanemiz
#include <map>

// 1. DİLİN HAFIZASI (BELLEK)
std::map<std::string, int> bellek;

// 2. KÜTÜPHANE KATMANI (KOMUT İŞLEYİCİ)
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
        std::cout << "[DeterCode CALC]: Hesaplama motoru devrede." << std::endl;
    }
    else {
        std::cout << "[HATA]: Bilinmeyen komut -> " << komut << std::endl;
    }
}

// 3. MOTOR KATMANI
void runDeterCode(std::string kodSatiri) {
    if (kodSatiri.empty() || kodSatiri[0] == '#') return; // Boş satırları ve yorum satırlarını atla
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut;
    komutIsle(komut, ss);
}

// 4. DİNAMİK MARŞ MOTORU (Dosyadan Okuyan Main)
int main() {
    std::cout << "=== DETERCODE MOTORU SCRIPTI OKUMAYA BASLIYOR ===" << std::endl;
    
    std::ifstream dosya("kod.deter"); // Dışarıdaki kod dosyasını açıyoruz
    if (!dosya.is_open()) {
        std::cout << "[SISTEM HATASI]: kod.deter dosyasi bulunamadi!" << std::endl;
        return 1;
    }

    std::string satir;
    while (std::getline(dosya, satir)) {
        runDeterCode(satir); // Dosyadaki her satırı tek tek motora yediriyoruz
    }

    dosya.close();
    std::cout << "=== SCRIPT BASARIYLA ISTANBUL SEMALARINDA KOSULDU ===" << std::endl;
    return 0;
}
