#ifndef OCCLUSION_CULLER_H
#define OCCLUSION_CULLER_H

#include <iostream>

class OcclusionCuller {
public:
    OcclusionCuller() {
        std::cout << "[👁️ CULL-ADVANCED]: Occlusion_Culler aktif. Duvar arkasindakiler gizlenecek." << std::endl;
    }

    // Onumuzdeki devasa binanin arkasinda kalan ve gorunmeyen arabalari cizimden eleyen zeka
    bool is_occluded_by_wall(float targetX, float wallX) {
        if (targetX > wallX) {
            std::cout << "[✂️ OCCLUDED]: Nesne binanin arkasinda kaldi, GPU'ya gonderilmedi!" << std::endl;
            return true; // Gizle usta
        }
        return false;
    }
};

#endif

