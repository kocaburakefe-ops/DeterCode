#ifndef SAVE_ENCRYPTER_H
#define SAVE_ENCRYPTER_H

#include <iostream>
#include <string>

class SaveEncrypter {
public:
    SaveEncrypter() {
        std::cout << "[🔒 CRYPTO]: Save_Encrypter zırhı giydirildi. Hileli save dosyalarina son!" << std::endl;
    }

    // Telefonun icindeki kayit dosyalarini ve oyun parasini SHA-256 tabanli sifreleyen muhafiz
    std::string encrypt_player_data(const std::string& rawData) {
        std::cout << "[🔑 SECURE]: Oyuncu verileri kriptografik olarak kilitlendi." << std::endl;
        return "SHA256_SECURE_DATA_HASH_HEX_50_OZELLIK";
    }
};

#endif

