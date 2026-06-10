#include "recovery_registry.h"

namespace DeterEngine {
    namespace AutoPilot {

        ErrorProfile get_recovery_profile(const char* error_code) {
            // Basit bir karar mantığı (Hangi hataya ne tepki verilecek?)
            if (std::string(error_code) == "OVERHEAT") {
                return {ErrorSeverity::CRITICAL, "Emergency_Cooling_Cycle"};
            }
            return {ErrorSeverity::LOW, "Log_Only"};
        }

    }
}
