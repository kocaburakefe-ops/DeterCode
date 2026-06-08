#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <jni.h>

// 1. DİLİN HAFIZASI
std::map<std::string, int> bellek;

// 2. KÜTÜPHANE KATMANI
void komutIsle(std::string komut, std::stringstream& ss) {
    if (komut == "LOG") {
        std::string arguman;
        ss >> arguman;

        if (bellek.find(arguman) != bellek.end()) {
            std::cout << "[DeterCode LOG]: " << arguman << " = " << bellek[arguman] << std::endl;
        } else {
            std::string geriKalan;
            std::getline(ss, geriKalan);
            std::cout << "[DeterCode LOG]: " << arguman << geriKalan << std::endl;
        }
    }
    else if (komut == "SET") {
        std::string degisken, esittir, deger;
        ss >> degisken >> esittir >> deger;
        try {
            bellek[degisken] = std::stoi(deger);
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

