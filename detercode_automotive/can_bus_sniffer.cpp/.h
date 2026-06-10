#ifndef CAN_BUS_SNIFFER_H
#define CAN_BUS_SNIFFER_H

#include <cstdint> // Standart veri tipleri için

// Arabanın CAN hattından gelen 8 byte'lık ham paket (Standart Frame)
struct CanFrame {
    uint32_t id;          // Beyin kimliği (Örn: 0x316 = Motor Devri)
    uint8_t  length;      // Veri boyutu
    uint8_t  data[8];     // Arabanın ciğerinden akan ham veriler
};

// CAN Hattı dinleme motorunu başlatan ana fonksiyon
void start_can_bus_sniffing();

#endif // CAN_BUS_SNIFFER_H

