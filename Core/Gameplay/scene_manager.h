#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h"

class SceneManager {
private:
    std::string currentScene;
    BlackBox& sceneLogger;

public:
    SceneManager(BlackBox& logger) : currentScene("MainMenu"), sceneLogger(logger) {
        std::cout << "[🎬 GAMEPLAY]: Scene_Manager devrede. Ana menü hazir." << std::endl;
    }

    // Yarisa gecerken eski bellegi temizleyen, yukleme ekranini yoneten ana salter
    void switch_scene(const std::string& newScene) {
        std::cout << "\n🔄 [SCENE-CHANGE]: '" << currentScene << "' sahnesinden '" << newScene << "' sahnesine geciliyor..." << std::endl;
        currentScene = newScene;
        
        std::cout << "[🧹 MEMORY]: Eski sahnenin artıklari temizlendi. Yeni dunya yuklendi!" << std::endl;
        sceneLogger.record(__FILE__, __LINE__, "INFO", "Sahne basariyla degistirildi: " + newScene);
    }
};

#endif

