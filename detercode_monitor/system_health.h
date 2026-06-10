#ifndef SYSTEM_HEALTH_H
#define SYSTEM_HEALTH_H

#include <string>

// Sistemde kritik bir hata oluştuğunda tetiklenen "Kara Kutu" fonksiyonu
void log_critical_error(const std::string& error_msg);

// CPU, RAM ve Isı değerlerini analiz edip otonom karar veren beyin
void analyze_system_load();

#endif

