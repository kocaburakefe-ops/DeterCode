#ifndef INTEGRITY_CHECK_H
#define INTEGRITY_CHECK_H

namespace DeterEngine {
    namespace Security {
        // Sistem dosya bütünlüğünü doğrula
        bool verify_system_integrity();
        
        // Sistemi dış dünyaya kapat, sadece yetkili komutları kabul et
        void apply_security_seal();
    }
}

#endif
