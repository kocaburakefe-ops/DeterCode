#include <iostream>
#include <string>
#include <sstream>
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
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut;
    komutIsle(komut, ss);
}

// 4. SAF KAN LINUX MARŞ MOTORU (MAIN)
int main() {
    std::cout << "=== DETERCODE MOTORU LINUX UZERINDE BASLATILDI ===" << std::endl;
    
    // Test Komutlarımızı Motora Gönderiyoruz:
    runDeterCode("SET beygir = 150");
    runDeterCode("LOG beygir");
    runDeterCode("LOG Sanayiye Selam Olsun!");
    runDeterCode("CALC");
    
    std::cout << "=== TESTLER BASARIYLA TAMAMLANDI ===" << std::endl;
    return 0;
}

