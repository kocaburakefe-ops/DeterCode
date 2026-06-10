#ifndef THERMAL_BYPASS_H
#define THERMAL_BYPASS_H

// İşlemcinin termal kısıtlamalarını yöneten fonksiyon
void manage_thermal_limits(bool enable_bypass);

// Güncel sıcaklığı ve kısıtlamayı kontrol eder
float get_system_temp();

#endif

