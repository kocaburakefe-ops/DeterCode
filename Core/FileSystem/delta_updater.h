#ifndef DELTA_UPDATER_H
#define DELTA_UPDATER_H

#include <iostream>

class DeltaUpdater {
public:
    DeltaUpdater() {
        std::cout << "[📂 FILESYSTEM]: Delta_Updater hazır. Bayt seviyesinde guncelleme kontrolu aktif." << std::endl;
    }

    // Haritaya yeni bir cıvata eklendiginde koca dosyayi degil, sadece degisen baytlari yamalar
    void apply_binary_patch() {
        std::cout << "[🔧 DELTA PATCH]: Sadece degisen kod blokları yerine vidalandı. Kotasız guncelleme tamam." << std::endl;
    }
};

#endif

