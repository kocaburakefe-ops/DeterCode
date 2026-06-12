#ifndef AUDIO_MIXER_H
#define AUDIO_MIXER_H

#include <iostream>
#include <string>
#include "../Diagnostics/blackbox.h"

class AudioMixer {
private:
    int activeChannels;
    BlackBox& audioLogger;

public:
    AudioMixer(BlackBox& logger) : activeChannels(0), audioLogger(logger) {
        std::cout << "[🔊 AUDIO]: Audio_Mixer aktif. Donanimsal ses kanallari acildi!" << std::endl;
    }

    // Egzoz sesi, fren sesi gibi efektleri milisaniyelik gecikme olmadan hoparlöre üfler
    void play_sound_instant(const std::string& soundEffect) {
        activeChannels++;
        std::cout << "[🎛️ SOUND]: '" << soundEffect << "' efekti sifir gecikmeyle oynatiliyor." << std::endl;

        if (activeChannels > 32) { // Eğer aynı anda 32'den fazla ses patlarsa donanımı koru
            audioLogger.record(__FILE__, __LINE__, "WARNING", "Ses kanalları maksimum sınıra ulaştı!");
        }
    }

    void clear_channels() {
        activeChannels = 0;
    }
};

#endif

