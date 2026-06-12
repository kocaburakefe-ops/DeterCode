#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <iostream>
#include <string>

class BehaviorTree {
public:
    BehaviorTree() {
        std::cout << "[🤖 AI-BRAIN]: Behavior_Tree aktif. Botlar artik kararlar alabilecek!" << std::endl;
    }

    // Rakip bot arabalarin otobanda makas mi atacagina yoksa fren mi yapacagina karar veren mekanizma
    std::string evaluate_bot_decision(int distanceToPlayer, bool isTargetInFront) {
        if (isTargetInFront && distanceToPlayer < 15) {
            return "MAKAS_AT_VE_SOLA_KIR";
        }
        if (distanceToPlayer < 5) {
            return "PANIK_FREN_YAP";
        }
        return "GAZ_LAMAYA_DEVAM";
    }
};

#endif

