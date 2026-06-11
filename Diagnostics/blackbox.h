#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Telefonda dosyaya yazabilmek için usta!

struct AdvancedLog {
    std::string time;
    std::string file;
    int line;
    std::string level; // INFO, WARNING, CRITICAL
    std::string msg;
    size_t active_ram; // O an harcanan RAM miktarı
};

class BlackBox {
private:
    std::vector<AdvancedLog> secureBuffer;
    size_t maxEntries;
    size_t currentRamUsage; // Motorun anlık RAM tüketimi takipçisi

public:
    BlackBox(size_t capacity = 1000) : maxEntries(capacity), currentRamUsage(0) {
        std::cout << "[⚡ BLACKBOX PRO]: Askeri standartta zırhlı koruma hücresi kuruldu!" << std::endl;
    }

    // RAM takibi için simülasyon fonksiyonu
    void update_ram_metric(size_t bytes) {
        currentRamUsage = bytes;
    }

    // 🛠️ ZIRHLI KAYIT ALMA
    void record(const std::string& file, int line, const std::string& level, const std::string& msg) {
        if (secureBuffer.size() >= maxEntries) {
            secureBuffer.erase(secureBuffer.begin()); // Eskileri sil, taze kayıtlara yer aç
        }

        AdvancedLog log = {"21:30:00", file, line, level, msg, currentRamUsage};
        secureBuffer.push_back(log);

        // Eğer hata CRITICAL (Ölümcül) ise, sistemin çökmesini bekleme, ŞALTERİ İNDİR!
        if (level == "CRITICAL") {
            trigger_panic_switch();
        }
    }

private:
    // 🔥 PANİK ŞALTERİ: SİSTEMİ ÇÖKMEDEN YAKALA VE DOSYAYA BAS
    void trigger_panic_switch() {
        std::cout << "\n[🚨🚨 CRITICAL PANIC DETECTED! SİSTEM KİLİTLENİYOR, VERİLER KURTARILIYOR... 🚨🚨]" << std::endl;
        
        // Telefonda veya bilgisayarda "deterengine_blackbox.txt" adında bir dosya açıp içine her şeyi kusuyoruz
        std::ofstream file("deterengine_blackbox.txt");
        if (file.is_open()) {
            file << "=== DETERENGINE BLACKBOX FLIGHT RECORDER ===" << std::endl;
            for (const auto& log : secureBuffer) {
                file << "[" << log.time << "] [" << log.level << "] File: " << log.file 
                     << " (Line: " << log.line << ") | RAM: " << log.active_ram << " Bytes | Msg: " << log.msg << std::endl;
            }
            file << "============================================" << std::endl;
            file.close();
            std::cout << "[💾 BLACKBOX]: Tüm suç mahalli 'deterengine_blackbox.txt' dosyasına mühürlendi! Güvendesiniz." << std::endl;
        } else {
            // Dosya açılamazsa ekrana bas usta, hiçbir şey kaybolmasın!
            std::cout << "[ERROR]: Dosya yazılamadı, ekrana dökülüyor:" << std::endl;
            for (const auto& log : secureBuffer) {
                std::cout << "-> " << log.msg << std::endl;
            }
        }
        
        // Burada sistemi güvenli bir şekilde sonlandırıyoruz ki donanım zarar görmesin
        exit(1); 
    }
};
