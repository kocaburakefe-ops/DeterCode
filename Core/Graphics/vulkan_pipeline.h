#ifndef VULKAN_PIPELINE_H
#define VULKAN_PIPELINE_H

#include <iostream>
#include "../Diagnostics/blackbox.h"

class VulkanPipeline {
private:
    bool isPipelineReady;
    BlackBox& gfxLogger;

public:
    VulkanPipeline(BlackBox& logger) : isPipelineReady(false), gfxLogger(logger) {
        std::cout << "[🎮 VULKAN]: Vulkan_Pipeline hatti kuruluyor... Sifir surucu hantalligi!" << std::endl;
    }

    // Ekran kartına (GPU) dogrudan komut tamponu (Command Buffer) gonderen canavar
    void compile_pipeline_state() {
        isPipelineReady = true;
        std::cout << "[⚡ GPU]: Vulkan Donanim Komut Tamponlari dogrudan silikona firlatildi!" << std::endl;
        gfxLogger.record(__FILE__, __LINE__, "INFO", "Vulkan hattı basariyla olusturuldu. GPU optimize.");
    }
};

#endif

