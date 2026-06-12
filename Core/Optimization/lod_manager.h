#ifndef LOD_MANAGER_H
#define LOD_MANAGER_H

#include <iostream>

class LODManager {
public:
    LODManager() {
        std::cout << "[⚙️ LOD]: LOD_Manager kuruldu. Kademeli detay yonetimi hazir." << std::endl;
    }

    // Uzaktaki arabalarin modelini dusuk detayli, yakindakileri yuksek detayli gosteren zeka
    int determine_lod_level(float distanceToCamera) {
        if (distanceToCamera > 150.0f) return 3; // En dusuk detay (Sadece birkac ucgen)
        if (distanceToCamera > 50.0f)  return 2; // Orta detay
        return 1;                                // En yuksek detay (Safkan kalite)
    }
};

#endif

