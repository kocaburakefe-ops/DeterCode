#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include "../Diagnostics/blackbox.h"

class ThreadWorker {
private:
    std::vector<std::thread> workerPool;
    size_t coreCount;
    BlackBox& threadLogger;

public:
    ThreadWorker(BlackBox& logger) : threadLogger(logger) {
        // Telefonun fiziksel olarak kaç tane çekirdeği (Core) varsa onu tık diye öğreniyoruz usta!
        coreCount = std::thread::hardware_concurrency();
        std::cout << "[🧵 CONCURRENCY]: Telefonun " << coreCount << " adet canavar cekirdegi tespit edildi!" << std::endl;
    }

    // Ağır işleri (Mesela yapay zeka hesaplamalarını veya harita yüklemeyi) arka çekirdeklere yıkar
    void deploy_task_to_background(std::function<void()> task) {
        if (workerPool.size() >= coreCount) {
            // Eğer bütün çekirdekler doluysa kara kutuya yaz usta, motoru boğmayalım
            threadLogger.record(__FILE__, __LINE__, "WARNING", "Tum islemci cekirdekleri dolu! Yeni gorev bekletiliyor.");
            return;
        }

        // Safkan C++ Thread yapısı ile yeni çekirdekte işi ateşle!
        workerPool.push_back(std::thread(task));
    }

    // İşlerin bitmesini bekleyen ve çekirdekleri temizleyen mekanizma
    void synchronize_workers() {
        for (auto& th : workerPool) {
            if (th.joinable()) {
                th.join(); // İş bitince çekirdeği serbest bırak
            }
        }
        workerPool.clear();
    }
};

