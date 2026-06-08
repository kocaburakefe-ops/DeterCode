#include <iostream>
#include <string>
#include <fstream>

// parser.cpp içindeki ana motor fonksiyonunu buraya bağlıyoruz
void runDeterCode(std::string kodSatiri);

int main() {
    std::cout << "=== MODULER DETERCODE MOTORU CALISIYOR ===" << std::endl;
    
    std::ifstream dosya("kod.deter");
    if (!dosya.is_open()) {
        std::cout << "[SISTEM HATASI]: kod.deter dosyasi bulunamadi!" << std::endl;
        return 1;
    }

    std::string satir;
    while (std::getline(dosya, satir)) {
        runDeterCode(satir); // Her satırı parser modülüne pasla
    }

    dosya.close();
    std::cout << "=== MODULER SCRIPT BASARIYLA TAMAMLANDI ===" << std::endl;
    return 0;
}
