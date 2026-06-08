#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// parser.cpp içindeki fonksiyonu güncelliyoruz: artık hangi satırda olduğumuzu bilecek ve değiştirebilecek
void runDeterCodeWithIndex(const std::vector<std::string>& tumSatirlar, int& currentIndex);

int main() {
    std::cout << "=== KRANK MILLI MODULER DETERCODE MOTORU CALISIYOR ===" << std::endl;
    
    std::ifstream dosya("kod.deter");
    if (!dosya.is_open()) {
        std::cout << "[SISTEM HATASI]: kod.deter dosyasi bulunamadi!" << std::endl;
        return 1;
    }

    // Dosyadaki tüm satırları hafızaya (vektöre) yüklüyoruz ki ileri-geri zıplayabilelim
    std::vector<std::string> kodSatirlari;
    std::string satir;
    while (std::getline(dosya, satir)) {
        kodSatirlari.push_back(satir);
    }
    dosya.close();

    // Satır satır okuma mekanizması (currentIndex dinamik olarak değişebilecek)
    int currentIndex = 0;
    while (currentIndex < kodSatirlari.size()) {
        runDeterCodeWithIndex(kodSatirlari, currentIndex);
        currentIndex++; // Normal şartta bir sonraki satıra geç
    }

    std::cout << "=== MODULER SCRIPT BASARIYLA TAMAMLANDI ===" << std::endl;
    return 0;
}
