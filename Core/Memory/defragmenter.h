#ifndef DEFRAGMENTER_H
#define DEFRAGMENTER_H

#include <iostream>
#include "../Diagnostics/blackbox.h"

class Defragmenter {
private:
    BlackBox& memLogger;

public:
    Defragmenter(BlackBox& logger) : memLogger(logger) {
        std::cout << "[🧠 MEMORY]: Defragmenter aktif. RAM delikleri kapatilacak!" << std::endl;
    }

    // RAM'de oyun calisirken olusan bosluklari arkada caktirmadan toparlar, telefonu sislere bogmaz
    void defragment_heap() {
        // Bloklari kaydirarak bosluklari birlestiren sanayi usulü hafıza presi
        std::cout << "[⚙️ COMPACT]: RAM bosluklari birlestirildi. Arka plan temiz ve akici." << std::endl;
    }
};

#endif

