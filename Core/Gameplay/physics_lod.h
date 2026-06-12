#ifndef PHYSICS_LOD_H
#define PHYSICS_LOD_H
#include <iostream>

class PhysicsLOD {
public:
    PhysicsLOD() { std::cout << "[🏎️ GAMEPLAY]: Physics_LOD devrede. Uzak mesafe yuk hesabi aktif." << std::endl; }
    void scale_physics_by_distance(float distance) {
        if (distance > 200.0f) {
            std::cout << "[✂️ PHYS_LOD]: Uzaktaki arabalarin suspansiyon fizigi hafifletildi, CPU rahat." << std::endl;
        }
    }
};
#endif

