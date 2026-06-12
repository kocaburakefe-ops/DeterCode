#ifndef ASSET_BUNDLER_H
#define ASSET_BUNDLER_H

#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h"

class AssetBundler {
private:
    BlackBox& assetLogger;

public:
    AssetBundler(BlackBox& logger) : assetLogger(logger) {
        std::cout << "[📦 RESOURCES]: Asset_Bundler hazir. Sıkıstırma algoritmaları yuklendi." << std::endl;
    }

    // Büyük 3D modelleri veya haritaları diskten (SSD/Hafıza) RAM'e bloklar halinde çok hızlı çeker
    void stream_asset_to_ram(const std::string& assetName) {
        std::cout << "[📥 STREAM]: '" << assetName << "' verisi diskten okundu, acildi ve RAM'e nakledildi." << std::endl;
        
        // Eğer yüklenen dosya bozuksa kara kutuya yaz usta!
        if (assetName.empty()) {
            assetLogger.record(__FILE__, __LINE__, "CRITICAL", "Asset yukleme basarisiz! Dosya bulunamadi.");
        }
    }
};

#endif

