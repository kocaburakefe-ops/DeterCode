#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <jni.h>

// 1. DİLİN HAFIZASI (BELLEK)
std::map<std::string, int> bellek;

// 2. KÜTÜPHANE KATMANI (KOMUT İŞLEYİCİ)
void komutIsle(std::string komut, std::stringstream& ss) {
    if (komut == "LOG") {
        std::string mesaj;
        std::getline(ss, mesaj);
        std::cout << "[DeterCode LOG]: " << mesaj << std::endl;
    }
    else if (komut == "SET") {
        std::string degisken, esittir, deger;
        ss >> degisken >> esittir >> deger;
        try {
            bellek[degisken] = std::stoi(deger); // Hafızaya kaydet
            std::cout << "[DeterCode SET]: " << degisken << " = " << deger << " olarak hafizalandi." << std::endl;
        } catch (...) {
            std::cout << "[HATA]: Sayisal deger donusturulemedi." << std::endl;
        }
    }
    else if (komut == "CALC") {
        std::cout << "[DeterCode CALC]: Hesaplama motoru devrede." << std::endl;
    }
    else {
        std::cout << "[HATA]: Bilinmeyen komut -> " << komut << std::endl;
    }
}

// 3. MOTOR KATMANI
void runDeterCode(std::string kodSatiri) {
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut;
    komutIsle(komut, ss);
}

// 4. ANDROID (JNI) KÖPRÜSÜ
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_detercode_MainActivity_runDeter(JNIEnv* env, jobject /* this */, jstring kod) {
    const char *nativeString = env->GetStringUTFChars(kod, 0);
    std::string kodSatiri = nativeString;
    
    runDeterCode(kodSatiri); 
    
    env->ReleaseStringUTFChars(kod, nativeString);
    return env->NewStringUTF("DeterCode: Komut basariyla islendi!");
}
