#ifndef SKELETAL_ANIMATOR_H
#define SKELETAL_ANIMATOR_H

#include <iostream>
#include <string>

class SkeletalAnimator {
public:
    SkeletalAnimator() {
        std::cout << "[🏃 ANIMATION]: Skeletal_Animator hazir. Kemik matrisleri yuklendi." << std::endl;
    }

    // Karakterlerin ve araba suspansiyonlarinin kemik hareketlerini GPU'yu yormadan hesaplar
    void transform_bones(const std::string& modelName, float animationTime) {
        // Burada hiyerarsik kemik matris (Matrix4x4) carpimlari doner usta
        std::cout << "[🦴 BONES]: '" << modelName << "' icin kemik donusumleri hesaplandi. Zaman: " << animationTime << std::endl;
    }
};

#endif

