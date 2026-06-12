#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <iostream>
#include <queue>
#include <string>
#include "../Diagnostics/blackbox.h"

struct GameEvent {
    std::string type; // TOUCH_DOWN, TOUCH_UP, KEY_PRESS
    int x;
    int y;
};

class EventDispatcher {
private:
    std::queue<GameEvent> inputQueue;
    BlackBox& inputLogger;

public:
    EventDispatcher(BlackBox& logger) : inputLogger(logger) {
        std::cout << "[🕹️ INPUT]: Event_Dispatcher aktif. Sifir gecikmeli dokunmatik kuyrugu hazir!" << std::endl;
    }

    // Donanımdan (ekrandan) gelen sinyali bürokrasiye takılmadan anında kuyruğa alır
    void push_hardware_event(const std::string& eventType, int posX, int posY) {
        GameEvent ev = {eventType, posX, posY};
        inputQueue.push(ev);
        
        // Eğer çok hızlı ardı ardına basılırsa (Combo anları) hafıza şişmesin diye takip ederiz
        if (inputQueue.size() > 100) {
            inputLogger.record(__FILE__, __LINE__, "WARNING", "Input kuyrugu sisiyor! Oyuncu ekrana cok hizli basiyor.");
        }
    }

    // Oyun döngüsü bu fonksiyonla sinyalleri anında eritir
    void dispatch_next_event() {
        if (!inputQueue.empty()) {
            GameEvent currentEvent = inputQueue.front();
            // Sinyali doğrudan fizik veya script motoruna fırlat usta!
            inputQueue.pop();
        }
    }
};

#endif

