#ifndef WIND_TUNNEL_SIM_H
#define WIND_TUNNEL_SIM_H
#include <iostream>

class WindTunnelSim {
public:
    WindTunnelSim() { std::cout << "[🌪️ PHYSICS]: Wind_Tunnel_Sim aktif. Aerodinamik surtunme devrede." << std::endl; }
    float calculate_drag_force(float speed) {
        std::cout << "[🏎️ DRAG]: Hız: " << speed << " km/h. Ruzgar direnci kaportaya basıyor." << std::endl;
        return speed * 0.15f;
    }
};
#endif

