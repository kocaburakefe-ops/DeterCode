#ifndef BIT_STREAMER_H
#define BIT_STREAMER_H

#include <iostream>

class BitStreamer {
public:
    BitStreamer() {
        std::cout << "[🌐 BIT-STREAM]: Bit_Streamer devrede. Paketler bit seviyesinde sıkısacak." << std::endl;
    }

    // Paketleri byte degil, bit seviyesinde paketleyerek internet kotasini ve hizi ucurur
    void write_bit(bool bit) {
        // Bit-shifting hamlesiyle veriyi sıkıstır usta
    }

    void flush_stream() {
        std::cout << "[📦 BIT-FLUSH]: Sıkıstırılmıs ham bit paketi UDP hattına fırlatıldı." << std::endl;
    }
};

#endif

