#include "src/deter_lib.h"
#include <jni.h>

// Dilin hafızasını burada tanımlıyoruz ki kütüphane buna erişebilsin
std::map<std::string, int> bellek;

// Ana çalıştırma fonksiyonumuz
void runDeterCode(std::string kodSatiri) {
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut; // İlk kelimeyi al (LOG, SET, CALC vs.)

    // İşi tamamen kütüphaneye (deter_lib.h) devrediyoruz!
    komutIsle(komut, ss);
}

// Android (JNI) Köprüsü - Java tarafından gelen komutları yakalar
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_detercode_MainActivity_runDeter(JNIEnv* env, jobject /* this */, jstring kod) {
    const char *nativeString = env->GetStringUTFChars(kod, 0);
    std::string kodSatiri = nativeString;
    
    // Motoru tetikle!
    runDeterCode(kodSatiri); 
    
    env->ReleaseStringUTFChars(kod, nativeString);
    return env->NewStringUTF("DeterCode: Komut basariyla islendi!");
}

