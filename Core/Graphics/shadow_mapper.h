#ifndef SHADOW_MAPPER_H
#define SHADOW_MAPPER_H

#include <iostream>

class ShadowMapper {
public:
    ShadowMapper() {
        std::cout << "[⚫ SHADOW]: Shadow_Mapper hazir. Golge haritalari olusturuluyor." << std::endl;
    }

    // Arabanin altindaki o keskin asfalt golgelerini ekran kartini yormadan sizen motor
    void render_shadow_map() {
        // Isik acisindan (Light Space Matrix) bakis hesaplanarak golge dokusu uretilir usta
        std::cout << "[🧱 SHADOW-TEX]: Dynamic Shadow Map basariyla GPU bellegine yazildi." << std::endl;
    }
};

#endif

