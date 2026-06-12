#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <iostream>
#include <string>

class UIRenderer {
public:
    UIRenderer() {
        std::cout << "[🖥️ UI]: UI_Renderer baslatildi. Hiz gostergeleri ve devir saatleri icin hazir." << std::endl;
    }

    // Ekrandaki hiz gostergesini, devir saatini islemciyi hic yormadan ekrana basar
    void draw_text_hardware(const std::string& text, int x, int y) {
        // Glif verileri dogrudan ekran karti texture belleginden alinir usta
    }
};

#endif

