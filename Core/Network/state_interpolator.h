#ifndef STATE_INTERPOLATOR_H
#define STATE_INTERPOLATOR_H

#include <iostream>

class StateInterpolator {
public:
    StateInterpolator() {
        std::cout << "[🌐 NET-SMOOTH]: State_Interpolator hazir. Isinlanmalar (lag) engellenecek." << std::endl;
    }

    // Internet koptugunda veya yavasladiginda karsi arabanin pozisyonunu matematiksel olarak tahmin eder
    float interpolate_position(float lastKnownX, float targetX, float alpha) {
        // Saf dogrusal interpolasyon (LERP) - Karsi araba yag gibi akar, ekranda titremez!
        return lastKnownX + alpha * (targetX - lastKnownX);
    }
};

#endif

