#include <iostream>
#include <string>
#include <sstream>
#include "bellek.hpp"

void hesapla(std::stringstream& ss);

// IF mekanizması için durumu takip eden global kontrol kilitleri
bool ifModuAktif = false;
bool sartDogruMu = true;

void komutIsle(std::string komut, std::stringstream& ss) {
    // 1. Durum: Eğer bir IF bloğunun içindeysek ve şart yanlışsa, ENDIF gelene kadar hiçbir şeyi çalıştırma
    if (ifModuAktif && !sartDogruMu) {
        if (komut == "ENDIF") {
            ifModuAktif = false;
            sartDogruMu = true;
            std::cout << "[DeterCode IF]: Blok sonuna gelindi, normal akisa donuluyor." << std::endl;
        }
        return; // Şart yanlış olduğu için komutu işlemeden çıkıyoruz
    }

    // 2. Durum: Normal Komut İşleme Alanı
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
        // Format: IF beygir > 200
        std::string solArguman, karsilastirmaSimgesi, sagArguman;
        if (ss >> solArguman >> karsilastirmaSimgesi >> sagArguman) {
            ifModuAktif = true;
            int solDeger = degerGetir(solArguman);
            int sagDeger = degerGetir(sagArguman);

            // Şart kontrolü yapılıyor
            if (karsilastirmaSimgesi == ">") sartDogruMu = (solDeger > sagDeger);
            else if (karsilastirmaSimgesi == "<") sartDogruMu = (solDeger < sagDeger);
            else if (karsilastirmaSimgesi == "==") sartDogruMu = (solDeger == sagDeger);
            else if (karsilastirmaSimgesi == "!=") sartDogruMu = (solDeger != sagDeger);

            std::cout << "[DeterCode IF]: Karsilastirma yapildi -> " << solArguman << " (" << solDeger << ") " 
                      << karsilastirmaSimgesi << " " << sagArguman << " (" << sagDeger << ") -> " 
                      << (sartDogruMu ? "SART DOGRU" : "SART YANLIS") << std::endl;
        }
    }
    else if (komut == "ENDIF") {
        // Şart doğru olduğunda tetiklenen ENDIF bloğu kapatma işlemi
        ifModuAktif = false;
        sartDogruMu = true;
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

