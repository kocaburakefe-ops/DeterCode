#ifndef TELEMETRY_HUB_H
#define TELEMETRY_HUB_H

#include <iostream>
#include <string>

class TelemetryHub {
public:
    TelemetryHub() {
        std::cout << "[📊 ANALYTICS]: Telemetry_Hub sinsi takibe basladi. Performans casusu aktif." << std::endl;
    }

    // Motorun hangi virajda veya hangi vites gecisinde FPS dusurdugunu arka planda loglar
    void log_performance_metric(const std::string& metricName, float value) {
        if (value < 30.0f && metricName == "FPS") {
            std::cout << "[🚨 TELEMETRY]: Darbogaz Saptandı! " << metricName << " degeri dustu: " << value << std::endl;
        }
    }
};

#endif

