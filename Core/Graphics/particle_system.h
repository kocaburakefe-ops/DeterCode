#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <iostream>
#include "../Diagnostics/blackbox.h"

class ParticleSystem {
private:
    int maxParticles;
    BlackBox& gfxLogger;

public:
    ParticleSystem(BlackBox& logger) : maxParticles(5000), gfxLogger(logger) {
        std::cout << "[✨ EFFECTS]: Particle_System aktif. Nitro ve egzoz dumanina hazir!" << std::endl;
    }

    // Nitro patlamasindaki binlerce kivilcimi GPU uzerinde ayni anda ucurur
    void emit_particles(float originX, float originY, int count) {
        if (count > maxParticles) {
            gfxLogger.record(__FILE__, __LINE__, "WARNING", "Maksimum parcacik siniri zorlaniyor! Performans dusebilir.");
        }
        std::cout << "[🔥 EMITTER]: " << count << " adet parcacik uzaya firlatildi!" << std::endl;
    }
};

#endif

