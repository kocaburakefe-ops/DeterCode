#ifndef HAPTIC_SYNTHESIZER_H
#define HAPTIC_SYNTHESIZER_H

#include <iostream>

class HapticSynthesizer {
public:
    HapticSynthesizer() {
        std::cout << "[🎛️ INPUT]: Haptic_Synthesizer devrede. Titresim motoru frekans ayari yapildi." << std::endl;
    }

    // Yataktaki mucur yolu veya vites gecisindeki sarsintiyi telefona safkan frekans olarak basar
    void trigger_gear_haptic(int gear) {
        std::cout << "[📳 HAPTIC]: " << gear << ". vitese gecildi! Telefon motoru sarsıntı frekansı gonderdi." << std::endl;
    }
};

#endif

