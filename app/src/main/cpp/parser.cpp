#include <iostream>
#include <string>
#include <sstream>
#include "bellek.hpp"

void hesapla(std::stringstream& ss);

// IF-ELSE mekanizması için kontrol kilitleri
bool ifModuAktif = false;
bool sartDogruMu = true;
bool elseGecildiMi = false;

void komutIsle(std::string komut, std::stringstream& ss) {
    // 1. Durum: ELSE kelimesi geldiyse kutupları değiştiriyoruz
    if (komut == "ELSE") {
        elseGecildiMi = true;
        sartDogruMu = !sartDogruMu; // Şart doğruysa artık yanlış, yanlışsa artık doğru kabul ediliyor
        return;
    }

    if (komut == "ENDIF") {
        ifModuAktif = false;
        sartDogruMu = true;
        elseGecildiMi = false;
        return;
    }

    // 2. Durum: Eğer bir blok içindeysek ve şu anki geçerli şart yanlışsa komutu yut
    if (ifModuAktif && !sartDogruMu) {
        return;
    }

    // 3. Durum: Normal Komut İşleme Alanı
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
        hesapla(ss);
    }
    else if (komut == "IF") {
        std::string solArguman, karsilastirmaSimgesi, sagArguman;
        if (ss >> solArguman >> karsilastirmaSimgesi >> sagArguman) {
            ifModuAktif = true;
            elseGecildiMi = false;
            int solDeger = degerGetir(solArguman);
            int sagDeger = degerGetir(sagArguman);

            if (karsilastirmaSimgesi == ">") sartDogruMu = (solDeger > sagDeger);
            else if (karsilastirmaSimgesi == "<") sartDogruMu = (solDeger < sagDeger);
            else if (karsilastirmaSimgesi == "==") sartDogruMu = (solDeger == sagDeger);
            else if (karsilastirmaSimgesi == "!=") sartDogruMu = (solDeger != sagDeger);

            std::cout << "[DeterCode IF]: Karsilastirma -> " << solArguman << " (" << solDeger << ") " 
                      << karsilastirmaSimgesi << " " << sagArguman << " (" << sagDeger << ") -> " 
                      << (sartDogruMu ? "SART DOGRU" : "SART YANLIS") << std::endl;
        }
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
