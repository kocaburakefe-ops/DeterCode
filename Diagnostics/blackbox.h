#include <iostream>
#include <string>
#include <vector>

// Kara kutuya kaydedilecek her bir olayın yapısı
struct LogEntry {
    std::string timestamp; // Hatanın/Olayın gerçekleştiği an
    std::string file;      // Hangi kod dosyasında oldu (Örn: main.cpp)
    int line;              // Kodun kaçıncı satırında oldu
    std::string message;   // O an işlemcinin ne yaptığı (Örn: RAM'den yer istendi)
};

class BlackBox {
private:
    std::vector<LogEntry> flightRecorder; // Uçuş kayıt cihazı (RAM'deki gizli oda)
    size_t maxCapacity;                   // Kutunun maksimum alacağı kayıt sayısı

    // Telefonun saatini milisaniye cinsinden alan yardımcı fonksiyon
    std::string getCurrentTime() {
        // Normalde burada canlı saat fonksiyonu olur usta, şimdilik simüle ediyoruz
        return "20:15:32.412"; 
    }

public:
    BlackBox(size_t capacity = 500) {
        maxCapacity = capacity;
        std::cout << "[BLACKBOX]: " << maxCapacity << " kayit kapasiteli zirhli kara kutu devreye girdi!" << std::endl;
    }

    // 🛠️ KARA KUTUYA ANLIK KAYIT YAZMA FONKSİYONU
    // Bu makro benzeri yapı sayesinde hatanın olduğu DOSYAYI ve SATIRI otomatik çekeriz usta!
    void record(const std::string& file, int line, const std::string& message) {
        // Kutu dolduysa eski kayıtları temizle (Döngüsel kayıt)
        if (flightRecorder.size() >= maxCapacity) {
            flightRecorder.erase(flightRecorder.begin());
        }

        LogEntry entry = { getCurrentTime(), file, line, message };
        flightRecorder.push_back(entry);
    }

    // 🔥 SİSTEM PATLADIĞINDA AÇILACAK RAPOR (SUÇ MAHALLİ İNCELEME)
    void dump_and_rescue() {
        std::cout << "\n==================================================" << std::endl;
        std::cout << "🚨🚨🚨 DETERENGINE ACİL DURUM: KARA KUTU AÇILIYOR 🚨🚨🚨" << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << "[KUTU DURUMU]: Sistem cokmeden önceki son kayitlar:" << std::endl;

        for (const auto& log : flightRecorder) {
            std::cout << "⏱️ [" << log.timestamp << "] -> Dosya: " << log.file 
                      << " (Satir: " << log.line << ") | Islem: " << log.message << std::endl;
        }

        std::cout << "==================================================" << std::endl;
        std::cout << "💡 BAŞMÜHENDİS TAVSİYESİ: En son satiri incele, hatayi yok et!" << std::endl;
        std::cout << "==================================================\n" << std::endl;
    }
};
