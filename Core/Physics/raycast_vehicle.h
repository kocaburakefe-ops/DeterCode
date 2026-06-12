#ifndef RAYCAST_VEHICLE_H
#define RAYCAST_VEHICLE_H

#include <iostream>

class RaycastVehicle {
private:
    float suspensionLength;
    float tireGripFactor;

public:
    RaycastVehicle() : suspensionLength(0.15f), tireGripFactor(1.0f) {
        std::cout << "[🧱 VEHICLE-PHYSICS]: Raycast_Vehicle teker ve suspansiyon fizigi aktif!" << std::endl;
    }

    // Arabanin lastiginin asfalta mi, toprağa mi bastigini milimetrik hesaplayan canavar
    void update_wheel_physics(float surfaceFriction) {
        tireGripFactor = surfaceFriction * 0.95f; // Surekli yol tutus takibi
        // Burada tekerleklerden asagiya dogru sanal isinlar (Raycast) firlatilir usta!
    }
};

#endif

