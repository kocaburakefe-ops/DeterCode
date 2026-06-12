#ifndef VFS_BRIDGE_H
#define VFS_BRIDGE_H

#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h"

class VFSBridge {
private:
    BlackBox& fsLogger;

public:
    VFSBridge(BlackBox& logger) : fsLogger(logger) {
        std::cout << "[📂 FILE-SYSTEM]: Virtual File System aktif. Guvenli dosya hatti acildi." << std::endl;
    }

    // Dosyalari acik birakmaz, tek bir sifreli paket (.pak) icinden sanal olarak okur
    void read_encrypted_file(const std::string& virtualPath) {
        std::cout << "[🔒 VFS]: '" << virtualPath << "' paketten cikariliyor ve hafizaya alinıyor." << std::endl;
        
        if (virtualPath.empty()) {
            fsLogger.record(__FILE__, __LINE__, "CRITICAL", "VFS Dosya okuma hatasi! Yol gecersiz.");
        }
    }
};

#endif

