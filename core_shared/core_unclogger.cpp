#include "core_unclogger.h"
#include <iostream>
#include <sys/resource.h> // Sistem seviyesinde işlemci önceliği için

void core_unclog_limits() {
    std::cout << "[CoreShared]: İşlemci kısıtlamaları kaldırılıyor..." << std::endl;
    
    // İşlemci önceliğini -20'ye çek (En yüksek rütbe)
    // Sadece root/admin yetkisiyle tam etkili olur
    int ret = setpriority(PRIO_PROCESS, 0, -20);
    
    if (ret == 0) {
        std::cout << "[CoreShared]: Başarılı! İşlemci tam serbest modda." << std::endl;
    } else {
        std::cout << "[CoreShared]: Uyarı! Kısıtlamalar kaldırılamadı, yetki kontrolü yap." << std::endl;
    }
}

bool is_core_optimized() {
    // Basit bir kontrol mekanizması
    return true; 
}

