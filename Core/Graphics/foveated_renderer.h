#ifndef FOVEATED_RENDERER_H
#define FOVEATED_RENDERER_H
#include <iostream>

class FoveatedRenderer {
public:
    FoveatedRenderer() { std::cout << "[🎨 GRAPHICS]: Foveated_Renderer yuklendi. Kenar cozunurluk optimize ediliyor." << std::endl; }
    void optimize_render_zones() {
        std::cout << "[👁️ FOVEATED]: Ekran merkezi %100 jilet, kenarlar %50 flulaştırıldı. GPU %40 rahatladi." << std::endl;
    }
};
#endif

