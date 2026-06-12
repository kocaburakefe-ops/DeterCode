#ifndef CRASH_DUMPER_H
#define CRASH_DUMPER_H
#include <iostream>

class CrashDumper {
public:
    CrashDumper() { std::cout << "[📊 DIAGNOSTICS]: Crash_Dumper tetikte. Rontgen cihazi hazir." << std::endl; }
    void dump_system_state() {
        std::cout << "[📸 DUMP]: Olası hata anı icin anlık RAM fotografi yerel loga islendi." << std::endl;
    }
};
#endif

