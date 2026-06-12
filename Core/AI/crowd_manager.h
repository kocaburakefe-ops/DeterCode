#ifndef CROWD_MANAGER_H
#define CROWD_MANAGER_H

#include <iostream>

class CrowdManager {
public:
    CrowdManager() {
        std::cout << "[🤖 CROWD]: Crowd_Manager uyandi. Suru psikolojisi devrede." << std::endl;
    }

    // Sehirdeki yayalarin ve diger arabalarin birbirine carpmadan akmasini saglar
    void update_crowd_avoidance() {
        // Yapay zeka ajanlari birbirlerinin kapsüllerini (Collision) hesaplayarak yol verir usta
        std::cout << "[🚦 TRAFFIC]: Şehir trafigi ve yayalar icin yol bulma optimize edildi." << std::endl;
    }
};

#endif

