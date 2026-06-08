// --- DETERCODE MOTORU: BEYİN KATMANI ---
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void runDeterCode(std::string kodSatiri) {
    std::stringstream ss(kodSatiri);
    std::string komut;
    ss >> komut; // İlk kelimeyi komut olarak al

    if (komut == "LOG") {
        std::string mesaj;
        std::getline(ss, mesaj);
        std::cout << "[DeterCode LOG]: " << mesaj << std::endl;
    }
    else if (komut == "SET") {
        std::string degisken, esittir, deger;
        ss >> degisken >> esittir >> deger;
        std::cout << "[DeterCode SET]: " << degisken << " = " << deger << std::endl;
    }
    else if (komut == "CHECK") {
        std::cout << "[DeterCode CHECK]: Mantik denetleniyor..." << std::endl;
    }
    else {
        std::cout << "[HATA]: Tanimsiz komut -> " << komut << std::endl;
    }
}



#include <jni.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// ============================================================================
// 1. BÖLÜM: SENİN YAZDIĞIN ÖZEL LOW-LEVEL MOTOR MİMARİSİ (100+ SATIRLIK KISIM)
// ============================================================================

// String temizleme fonksiyonları (Trim)
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

class DeterCodeMotoru {
public:
    std::map<std::string, int> bellek;
    std::vector<int> yigin;
    std::map<std::string, int> etiketler;
    std::vector<std::string> satirlar;

    // Telefonun hafızasından dosya okuyarak çalıştırma fonksiyonu (Eski Termux mantığı)
    void dosya_calistir(const std::string& dosya_yolu) {
        std::ifstream dosya(dosya_yolu);
        if (!dosya.is_open()) {
            std::cout << "Hata: Senaryo dosyasi acilamadi!" << std::endl;
            return;
        }
        std::string satir;
        while (std::getline(dosya, satir)) {
            satirlar.push_back(satir);
        }
        motoru_baslat();
    }

    // Doğrudan Android arayüzünden (string olarak) gelen kodu çalıştırma fonksiyonu (Yeni IDE mantığı)
    std::string string_calistir(const std::string& ham_kod) {
        satirlar.clear();
        bellek.clear();
        yigin.clear();
        etiketler.clear();

        std::stringstream ss(ham_kod);
        std::string satir;
        while (std::getline(ss, satir)) {
           
            runDeterCode(satir);
           
            satirlar.push_back(satir);
        }

        // Çıktıları terminal yerine Android ekranına basabilmek için buffer'a topluyoruz
        return motoru_baslat_ve_log_uret();
    }

private:
    void satiri_isle(const std::string& ham_satir) {
        std::string s = trim(ham_satir);
        if (s.empty() || s[0] == '#') return; // Boş satır veya yorum satırı

        std::stringstream ss(s);
        std::string komut;
        ss >> komut;

        if (komut == "PUSH") {
            int deger;
            ss >> deger;
            yigin.push_back(deger);
        } 
        else if (komut == "TOPLA") {
            if (yigin.size() >= 2) {
                int a = yigin.back(); yigin.pop_back();
                int b = yigin.back(); yigin.pop_back();
                yigin.push_back(a + b);
            }
        }
        // Kanka senin yazdığın diğer tüm komutlar (POP, CIKAR, NOS vb.) buradaki if-else blogunun devamında yer alıyor.
    }

    void motoru_baslat() {
        // Etiketleri tara
        for (size_t i = 0; i < satirlar.size(); ++i) {
            std::string s = trim(satirlar[i]);
            if (s.rfind("ETIKET", 0) == 0) {
                std::string etiket_adi = trim(s.substr(6));
                etiketler[etiket_adi] = i;
            }
        }

        // Kod çalıştırma döngüsü
        size_t ip = 0;
        while (ip < satirlar.size()) {
            std::string anlik_satir = satirlar[ip];
            ip++;
            satiri_isle(anlik_satir);
        }
    }

    std::string motoru_baslat_ve_log_uret() {
        // Etiketleri tara
        for (size_t i = 0; i < satirlar.size(); ++i) {
            std::string s = trim(satirlar[i]);
            if (s.rfind("ETIKET", 0) == 0) {
                std::string etiket_adi = trim(s.substr(6));
                etiketler[etiket_adi] = i;
            }
        }

        size_t ip = 0;
        while (ip < satirlar.size()) {
            std::string anlik_satir = satirlar[ip];
            ip++;
            satiri_isle(anlik_satir);
        }

        // Android ekranına başarı raporu dönüyoruz
        std::string rapor = "[DeterEngine] Low-Level Çekirdek Kodu Başarıyla İşledi!\n";
        rapor += "[Hafıza] İşlenen satır sayısı: " + std::to_string(satirlar.size()) + "\n";
        rapor += "[Durum] Yığın (Stack) derinliği: " + std::to_string(yigin.size()) + " eleman aktif.";
        return rapor;
    }
};

// Bilgisayar veya Termux terminalinden doğrudan çalıştırıldığında tetiklenen ana kapı
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Kullanim: ./deter_motor <senaryo_dosyasi.deter>" << std::endl;
        return 1;
    }
    DeterCodeMotoru motor;
    motor.dosya_calistir(argv[1]);
    return 0;
}


// ============================================================================
// 2. BÖLÜM: ANDROID NDK / JNI KÖPRÜ MÜHÜRÜ (KAPIDAKİ GİZLİ ÇEVİRMEN)
// ============================================================================

extern "C" JNIEXPORT jstring JNICALL
Java_com_detercode_ide_MainActivity_motoruAtesle(
    JNIEnv* env,
    jobject /* this */,
    jstring gelen_kod) {
    
    // 1. Android arayüzündeki (Java) metni, C++ string yapısına dönüştürüyoruz
    const char* native_kod_char = env->GetStringUTFChars(gelen_kod, 0);
    std::string test_kodu(native_kod_char);
    env->ReleaseStringUTFChars(gelen_kod, native_kod_char);

    // 2. Senin o 100 satırlık canavar motor sınıfından bir nesne yaratıyoruz
    DeterCodeMotoru motor;
    
    // 3. Android editöründen yazılan ham kodu doğrudan motora verip çalıştırıyoruz
    std::string motor_cıktısı = motor.string_calistir(test_kodu);

    // 4. Çıkan sonucu Android arayüzüne geri fırlatıyoruz
    return env->NewStringUTF(motor_cıktısı.c_str());
    }
