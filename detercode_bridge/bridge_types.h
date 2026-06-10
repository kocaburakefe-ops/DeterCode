#ifndef BRIDGE_TYPES_H
#define BRIDGE_TYPES_H

namespace DeterEngine {
    namespace Bridge {
        // Sistem mesajlarının türlerini tanımlıyoruz
        enum class MessageType {
            INFO,       // Genel bilgi
            WARNING,    // Dikkat edilmesi gerekenler
            CRITICAL,   // Otopilotun devreye girmesi gereken hata
            COMMAND     // Sisteme doğrudan verilen emir
        };

        struct Message {
            MessageType type;
            const char* content;
        };
    }
}

#endif

