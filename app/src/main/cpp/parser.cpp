#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "bellek.hpp"

void hesapla(std::stringstream& ss);

// IF-ELSE kilitleri
bool ifModuAktif = false;
bool sartDogruMu = true;
bool elseGecildiMi = false;

// LOOP kilitleri (Geri zıplama noktası)
int loopBaslangicIndex = -1;

void komutIsle(std::string komut, std::stringstream& ss, const std::vector<std::string>& tumSatirlar, int& currentIndex) {
    
    // ELSE ve ENDIF Karar Mekanizmaları
    if (komut == "ELSE") {
        elseGecildiMi = true;
        sartDogruMu = !sartDogruMu;
        return;
    }
    if (komut == "ENDIF") {
        ifModuAktif = false;
        sartDogruMu = true;
        elseGecildiMi = false;
        return;
    }

    // IF şartı yanlışsa aradaki kodları yutma kilidi
    if (ifModuAktif && !sartDogruMu) return;

    // --- YENİ EKLENEN LOOP (DÖNGÜ) MEKANİZMASI ---
    if (komut == "LOOP") {
        std::string solArguman, karsilastirmaSimgesi, sagArguman;
        if (ss >> solArguman >> karsilastirmaSimgesi >> sagArguman) {
            int solDeger = degerGetir(solArguman);
            int sagDeger = degerGetir(sagArguman);
            bool loopSarti = false;

            if (karsilastirmaSimgesi == ">") loopSarti = (solDeger > sagDeger);
            else if (karsilastirmaSimgesi == "<") loopSarti = (solDeger < sagDeger);
            else if (karsilastirmaSimgesi == "==") loopSarti = (solDeger == sagDeger);
            else if (karsilastirmaSimgesi == "!=") loopSarti = (solDeger != sagDeger);

            if (loopSarti) {
                // Şart doğru, döngü başlıyor! Nerede olduğumuzu kaydedelim ki geri dönebilelim.
                loopBaslangicIndex = currentIndex; 
            } else {
                // Şart bitti, döngüyü kırıp ENDLOOP'un olduğu satıra kadar kodları atlıyoruz.
                while (currentIndex < tumSatirlar.size()) {
                    if (tumSatirlar[currentIndex].find("ENDLOOP") != std::string::npos) {
                        break;
                    }
                    currentIndex++;
                }
            }
        }
        return;
    }

    if (komut == "ENDLOOP") {
        // Döngünün sonuna geldik, motorun kafasını kaydedilen başlangıç noktasına geri çeviriyoruz!
        if (loopBaslangicIndex != -1) {
            currentIndex = loopBaslangicIndex - 1; 
        }
        return;
    }

    // --- NORMAL KOMUTLAR (LOG, SET, CALC, IF) ---
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
        }
    }
}

// Yeni ana motor bağlantısı (Satır numarasıyla birlikte çalışıyor)
void runDeterCodeWithIndex(const std::vector<std::string>& tumSatirlar, int& currentIndex) {
    std::string kodSatiri = tumSatirlar[currentIndex];
    if (kodSatiri.empty() || kodSatiri[0] == '#') return;
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut;
    komutIsle(komut, ss, tumSatirlar, currentIndex);
}
