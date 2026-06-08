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
    int ip = 0; // Instruction Pointer
    bool satir_atla = false;

    DeterCodeMotoru() {
        // V8.0 C++ Çekirdek Bellek Başlangıç Değerleri
        bellek["kahraman_can"] = 100;
        bellek["kahraman_max_can"] = 100;
        bellek["kahraman_hasar"] = 35;
        bellek["dusman_can"] = 200;
        bellek["dusman_max_can"] = 200;
        bellek["dusman_hamlesi"] = 0;
        bellek["secim"] = 0;
        bellek["son_hasar"] = 0;
        srand(time(0)); // Rastgelelik çekirdeği
    }

    std::string degiskenleri_coz(std::string metin) {
        for (auto const& [anahtar, deger] : bellek) {
            size_t pos = metin.find(anahtar);
            while (pos != std::string::npos) {
                metin.replace(pos, anahtar.length(), std::to_string(deger));
                pos = metin.find(anahtar, pos + std::to_string(deger).length());
            }
        }
        return metin;
    }

    void matematik_isle(std::string satir) {
        size_t eq_pos = satir.find('=');
        if (eq_pos == std::string::npos) return;

        std::string var_name = trim(satir.substr(0, eq_pos));
        std::string expr = trim(satir.substr(eq_pos + 1));
        expr = degiskenleri_coz(expr);

        // Basit matematik çözücü (A = B - C veya A = B + C mantığı için)
        int sonuc = 0;
        std::stringstream ss(expr);
        int terim;
        char op;
        if (ss >> terim) {
            sonuc = terim;
            while (ss >> op >> terim) {
                if (op == '+') sonuc += terim;
                if (op == '-') sonuc -= terim;
            }
        }
        bellek[var_name] = sonuc;
        std::cout << "[BELLEK GÜNCELLENDİ] " << var_name << " -> " << sonuc << std::endl;
    }

    void satiri_isle(std::string satir) {
        satir = trim(satir);
        if (satir.empty() || satir.rfind("//", 0) == 0 || satir.rfind("ETİKET", 0) == 0) return;

        if (satir_atla) {
            satir_atla = false;
            return;
        }

        if (satir.rfind("yazdir", 0) == 0) {
            std::string mesaj = satir.substr(6);
            mesaj = trim(mesaj);
            if (!mesaj.empty() && mesaj.front() == '"') mesaj.erase(0, 1);
            if (!mesaj.empty() && mesaj.back() == '"') mesaj.pop_back();
            std::cout << degiskenleri_coz(mesaj) << std::endl;
        }
        else if (satir.rfind("GIRDI", 0) == 0) {
            std::string var_name = trim(satir.substr(5));
            int girdi_deger;
            std::cout << ">> ";
            std::cin >> girdi_deger;
            bellek[var_name] = girdi_deger;
        }
        else if (satir.rfind("RASTELE", 0) == 0) {
            std::string icerik = satir.substr(7);
            size_t eq_pos = icerik.find('=');
            std::string var_name = trim(icerik.substr(0, eq_pos));
            std::string aralik = trim(icerik.substr(eq_pos + 1));
            size_t tire_pos = aralik.find('-');
            int min_val = std::stoi(degiskenleri_coz(aralik.substr(0, tire_pos)));
            int max_val = std::stoi(degiskenleri_coz(aralik.substr(tire_pos + 1)));
            int rand_val = min_val + rand() % (max_val - min_val + 1);
            bellek[var_name] = rand_val;
            std::cout << "[NATIVE ZAR] " << var_name << " -> " << rand_val << std::endl;
        }
        else if (satir.rfind("EGER", 0) == 0) {
            std::string sart = satir.substr(4);
            sart = degiskenleri_coz(sart);
            // Basit karşılaştırma mantığı (A > B veya A < B veya A == B)
            bool durum = false;
            std::stringstream ss(sart);
            int sol, sag;
            std::string op;
            if (ss >> sol >> op >> sag) {
                if (op == ">") durum = (sol > sag);
                else if (op == "<") durum = (sol < sag);
                else if (op == "==") durum = (sol == sag);
            }
            satir_atla = !durum;
        }
        else if (satir.rfind("PUSH", 0) == 0) {
            std::string val_str = trim(satir.substr(4));
            int val = std::stoi(degiskenleri_coz(val_str));
            yigin.push_back(val);
            std::cout << "[STACK PUSH] " << val << std::endl;
        }
        else if (satir.rfind("POP", 0) == 0) {
            std::string var_name = trim(satir.substr(3));
            if (!yigin.empty()) {
                int val = yigin.back();
                yigin.pop_back();
                bellek[var_name] = val;
                std::cout << "[STACK POP] " << var_name << " = " << val << std::endl;
            }
        }
        else if (satir == "COP_TOPLA") {
            // C++ map mekanik temizliği: Değeri 0 olan geçici verileri temizle
            for (auto it = bellek.cbegin(), next_it = it; it != bellek.cend(); it = next_it) {
                ++next_it;
                if (it->second == 0 && it->first != "secim" && it->first != "son_hasar") {
                    bellek.erase(it);
                }
            }
        }
        else if (satir.rfind("GOTO", 0) == 0) {
            std::string hedef = trim(satir.substr(4));
            if (etiketler.find(hedef) != etiketler.end()) {
                ip = etiketler[hedef];
            }
        }
        else if (satir == "DURDUR") {
            std::cout << "[KAPATMA] C++ Çekirdeği görevini tamamladı." << std::endl;
            exit(0);
        }
        else if (satir.find('=') != std::string::npos) {
            matematik_isle(satir);
        }
    }

    void dosya_calistir(std::string dosya_yolu) {
        std::ifstream dosya(dosya_yolu);
        if (!dosya.is_open()) {
            std::cout << "[FATAL] " << dosya_yolu << " bulunamadı!" << std::endl;
            return;
        }
        std::string satir;
        while (std::getline(dosya, satir)) {
            satirlar.push_back(satir);
        }
        dosya.close();

        // 1. Geçiş: Etiket haritasını çıkar (Label Indexing)
        for (size_t i = 0; i < satirlar.size(); ++i) {
            std::string s = trim(satirlar[i]);
            if (s.rfind("ETİKET", 0) == 0) {
                std::string etiket_adi = trim(s.substr(6));
                etiketler[etiket_adi] = i;
            }
        }

        // 2. Geçiş: Kod çalıştırma döngüsü
        while (ip < satirlar.size()) {
            std::string anlik_satir = satirlar[ip];
            ip++;
            satiri_isle(anlik_satir);
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Kullanım: ./deter_motor <senaryo_dosyası.deter>" << std::endl;
        return 1;
    }
    DeterCodeMotoru motor;
    motor.dosya_calistir(argv[1]);
    return 0;
}



extern "C" JNIEXPORT jstring JNICALL
Java_com_detercode_ide_MainActivity_motoruAtesle(
    JNIEnv* env,
    jobject /* this */) {
    
    // BURADA SENİN MOTORU TETİKLEYECEĞİZ
    // Örneğin senin motorunun ana fonksiyonu neyse onu çağırabiliriz.
    // Şimdilik arayüze motorun hazır olduğu mesajını gönderiyoruz:
    
    std::string nativeMesaj = "[DeterEngine] 100+ Satırlık Çekirdek Motor Android NDK ile Bağlandı!";
    return env->NewStringUTF(nativeMesaj.c_str());
}

