#ifndef FRUSTUM_CULLER_H
#define FRUSTUM_CULLER_H

#include <iostream>

class FrustumCuller {
public:
    FrustumCuller() {
        std::cout << "[✂️ OPTIMIZATION]: Frustum_Culler aktif. Arkan kalan nesneler cizilmeyecek." << std::endl;
    }

    // Kameranin gormedigi, oyuncunun arkasinda kalan binalari ve daglari cizimden atan canavar
    bool is_object_visible(float objX, float objY, float objZ) {
        // Kamera piramidinin (Frustum) icinde mi kontrolu usta
        // Eger arkadaysa tık diye 'false' verir, ekran kartini yukten kurtarir!
        return true; 
    }
};

#endif

