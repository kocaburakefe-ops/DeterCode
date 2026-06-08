// 2. KÜTÜPHANE KATMANI (KOMUT İŞLEYİCİ)
void komutIsle(std::string komut, std::stringstream& ss) {
    if (komut == "LOG") {
        std::string arguman;
        ss >> arguman; // İlk kelimeyi alıyoruz (Değişken mi yoksa düz yazı mı?)

        // Hafızayı kontrol et: Bu kelime bellek haritasında var mı?
        if (bellek.find(arguman) != bellek.end()) {
            std::cout << "[DeterCode LOG]: " << arguman << " = " << bellek[arguman] << std::endl;
        } else {
            // Eğer hafızada yoksa, düz yazıdır. Satırın geri kalanını al ve birleştir
            std::string geriKalan;
            std::getline(ss, geriKalan);
            std::cout << "[DeterCode LOG]: " << arguman << geriKalan << std::endl;
        }
    }
    else if (komut == "SET") {
        std::string degisken, esittir, deger;
        ss >> degisken >> esittir >> deger;
        try {
            bellek[degisken] = std::stoi(deger); // Hafızaya kaydet
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

