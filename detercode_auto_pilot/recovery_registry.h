#ifndef RECOVERY_REGISTRY_H
#define RECOVERY_REGISTRY_H

namespace DeterEngine {
    namespace AutoPilot {

        // Hata tiplerini kategorize ediyoruz
        enum class ErrorSeverity {
            LOW,        // Sadece log al
            MEDIUM,     // Kaynağı yeniden başlat
            CRITICAL    // Güvenli moda geç
        };

        // Hata tipini belirleyen yapı
        struct ErrorProfile {
            ErrorSeverity severity;
            const char* recovery_action;
        };

        // Hata koduna göre profil döndüren fonksiyon
        ErrorProfile get_recovery_profile(const char* error_code);
        
    } // AutoPilot sonu
} // DeterEngine sonu

#endif

