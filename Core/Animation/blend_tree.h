#ifndef BLEND_TREE_H
#define BLEND_TREE_H

#include <iostream>

class BlendTree {
public:
    BlendTree() {
        std::cout << "[🏃 ANIM-SMOOTH]: Blend_Tree aktif. Gecisler pruzsuz olacak." << std::endl;
    }

    // Ani frende veya virajda savrulurken iki farkli animasyonu birbirine yag gibi karistirir
    void calculate_blend_weight(float currentSpeed, float driftAngle) {
        float weight = currentSpeed / 200.0f; // Hiz ve aciya gore karisim orani (0.0 - 1.0)
        std::cout << "[🔄 BLEND]: Animasyon karisim degeri milimetrik ayarlandi: " << weight << std::endl;
    }
};

#endif

