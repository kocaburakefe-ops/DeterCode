#ifndef DOPPLER_EFFECT_H
#define DOPPLER_EFFECT_H

#include <iostream>

class DopplerEffect {
public:
    DopplerEffect() {
        std::cout << "[🔊 DOPPLER]: Doppler_Effect aktif. Akustik fizik devrede." << std::endl;
    }

    // Yanimizdan hizla gecen bot arabanin sesinin yaklastikca incelip uzaklastikca kalinlasmasi
    float calculate_pitch_shift(float sourceSpeed, float listenerSpeed, float soundWaveSpeed) {
        // Saf ses fizigi formülü usta
        float pitchFactor = (soundWaveSpeed + listenerSpeed) / (soundWaveSpeed - sourceSpeed);
        return pitchFactor;
    }
};

#endif

