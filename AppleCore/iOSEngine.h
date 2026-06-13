#ifndef IOS_ENGINE_H
#define IOS_ENGINE_H

#include <iostream>

class iOSEngine {
public:
    iOSEngine();
    ~iOSEngine();

    // Diğer klasörlerdeki operasyonları tetikleyen ana motor kolları
    void igniteDeterAppleCore();   // AppleCore'daki dosyaları tetikler
    void deployDetercodeApple();   // Detercode_apple'daki zırhları kaldırır
    void unleashFullPerformance();  // Piyasaya şov yapacağımız saf güç döngüsü
};

#endif // IOS_ENGINE_H

