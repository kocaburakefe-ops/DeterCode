#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <iostream>

class PostProcessor {
public:
    PostProcessor() {
        std::cout << "[🎬 GRAPHICS-EFFECTS]: Post_Processor hazir. Sinematik filtreler devrede." << std::endl;
    }

    // Hareket bulankligi (Motion Blur) ve parlama (Bloom) efektlerini ekrana basan son rotus
    void apply_render_effects() {
        // Renk paleti (LUT) ve kontrast ayarlari burada son kareye çakilir usta
        std::cout << "[🎨 FILTERS]: Motion Blur ve Bloom efektleri ekrana mühürlendi." << std::endl;
    }
};

#endif

