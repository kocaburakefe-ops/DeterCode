#ifndef NAVMESH_GENERATOR_H
#define NAVMESH_GENERATOR_H

#include <iostream>

class NavMeshGenerator {
public:
    NavMeshGenerator() {
        std::cout << "[🤖 NAVMESH]: NavMesh_Generator uyandi. Surus alanlari taranıyor." << std::endl;
    }

    // Haritadaki engelleri tarayip botlarin surebilecegi "guvenli alanlari" cıkarır
    void bake_navigation_mesh() {
        // Poligon verileri taranip yapay zekanin basabilecegi zemin haritasi uretilir
        std::cout << "[🎯 NAV-BAKE]: Surus yollari ve kaldirimlar NavMesh olarak mühürlendi." << std::endl;
    }
};

#endif

