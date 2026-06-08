#include <iostream>
#include <sstream>
#include "bellek.hpp"

// Global belleği bu dosyaya da tanıtıyoruz
std::map<std::string, int> bellek;

void hesapla(std::stringstream& ss) {
    std::string hedefDegisken, esittir, arg1, operatorSimgesi, arg2;
    
    if (ss >> hedefDegisken >> esittir >> arg1 >> operatorSimgesi >> arg2) {
        int sayi1 = degerGetir(arg1);
        int sayi2 = degerGetir(arg2);
        int sonuc = 0;

        if (operatorSimgesi == "+") sonuc = sayi1 + sayi2;
        else if (operatorSimgesi == "-") sonuc = sayi1 - sayi2;
        else if (operatorSimgesi == "*") sonuc = sayi1 * sayi2;
        else if (operatorSimgesi == "/") {
            if (sayi2 != 0) sonuc = sayi1 / sayi2;
            else std::cout << "[HATA]: Sifira bolme hatasi!" << std::endl;
        }

        bellek[hedefDegisken] = sonuc;
        std::cout << "[DeterCode CALC]: " << hedefDegisken << " hesaplandi -> " << sonuc << std::endl;
    } else {
        std::cout << "[HATA]: CALC formati yanlis! (Orn: CALC a = b + c)" << std::endl;
    }
}

