#ifndef SELF_REPAIR_H
#define SELF_REPAIR_H

#include <string>

// Projenin tüm dosyalarını bağlayan "Dost İsim" çatımız
namespace DeterEngine {
    namespace AutoPilot {
        
        // Hata geldiğinde sistemi otomatik kurtaran mekanizma
        void attempt_self_repair(const std::string& error_code);

        // Servis moduna geçiş
        void enter_safe_mode();
        
    } // AutoPilot sonu
} // DeterEngine sonu

#endif

