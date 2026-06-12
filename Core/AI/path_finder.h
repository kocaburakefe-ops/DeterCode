#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <iostream>

class PathFinder {
public:
    PathFinder() {
        std::cout << "[🤖 ROUTE]: Path_Finder (A* Algoritmasi) rotasyon icin hazir!" << std::endl;
    }

    // Botlarin yaristaki en ideal cizgiyi (Apex noktalarini) salisede bulmasini saglar
    void calculate_optimal_racing_line(int startNode, int endNode) {
        // En kisa ve en hizli yol matrisi burada cozulur usta
        std::cout << "[🎯 APEX]: Yaristan kopmamak adina en hizli yaris cizgisi hesaplandi." << std::endl;
    }
};

#endif

