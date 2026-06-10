#ifndef OBD2_PROTOCOLS_H
#define OBD2_PROTOCOLS_H

#include <cstdint>

// OBD2 Protokol Tipleri - Arabanın beynine hangi "dilden" hitap edeceğimizi seçeriz
enum ObdProtocol {
    PROTOCOL_ISO_15765_4_CAN = 1, // Modern CAN protokolü
    PROTOCOL_KWP2000         = 2, // E36/E46 dönemi klasik ECU protokolü
    PROTOCOL_ISO_9141_2      = 3  // Eski tip K-Line haberleşme
};

// Beyinle bağlantı kurarken kullanılacak ana komut yapısı
struct ObdCommand {
    uint8_t mode;      // Mod: 0x01 Mevcut veriler, 0x03 Hata kodları
    uint8_t pid;       // PID: Hangi veriyi istiyoruz? (Örn: 0x0C = RPM)
    ObdProtocol proto; // Hangi dilde soruyoruz?
};

// Beyin bağlantısını başlatan fonksiyon prototipi
void initialize_obd2_connection(ObdProtocol protocol);

#endif // OBD2_PROTOCOLS_H

