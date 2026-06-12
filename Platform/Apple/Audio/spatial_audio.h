#ifndef SPATIAL_AUDIO_H
#define SPATIAL_AUDIO_H
#include <iostream>

class SpatialAudio {
public:
    SpatialAudio() { std::cout << "[🔊 AUDIO]: Spatial_Audio yuklendi. 3D Ses Sahnesi aktif." << std::endl; }
    void update_3d_sound(float sourceX, float sourceY) {
        std::cout << "[🎧 SPATIAL]: Rakip motor sesi konuma gore kulaklıga yonlendirildi: X:" << sourceX << " Y:" << sourceY << std::endl;
    }
};
#endif

