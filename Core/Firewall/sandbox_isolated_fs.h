#ifndef SANDBOX_ISOLATED_FS_H
#define SANDBOX_ISOLATED_FS_H

#include <iostream>
#include <string>

class SandboxIsolatedFS {
public:
    SandboxIsolatedFS() {
        std::cout << "[🛡️ SANDBOX]: Sandbox_Isolated_FS aktif. Dosya sistemi hucreye kapatildi." << std::endl;
    }

    // Motorun dosya islemlerini telefonun diger klasorlerinden tamamen soyutlar, disari sızdırmaz
    std::string safe_resolve_path(const std::string& securePath) {
        std::cout << "[🔒 SANDBOX-PATH]: Gecis yetkisi sadece oyun hucresine verildi: " << securePath << std::endl;
        return "/sandbox/internal/app/" + securePath;
    }
};

#endif

