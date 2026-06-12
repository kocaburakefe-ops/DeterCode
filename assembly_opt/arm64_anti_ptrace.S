// =========================================================================
// 🏛️ SÜTUN 3: DONANIMSAL ÇEKİRDEK SEVİYESİ ANTI-DEBUG (ARM64 SYSTEM CALL)
// =========================================================================
.global arm64_anti_ptrace_sys
.align 4

arm64_anti_ptrace_sys:
    // Kernel düzeyinde ptrace(PTRACE_TRACEME, 0, 1, 0) çağrısını hazırlıyoruz usta.
    // Amaç: İşletim sistemine "Ben zaten kendimi izliyorum, başka hiç kimse beni dinleyemez" demek.
    
    mov         x0, #0                  // PTRACE_TRACEME (0) -> İlk parametre
    mov         x1, #0                  // PID = 0 (Kendi sürecimiz) -> İkinci parametre
    mov         x2, #1                  // Üçüncü parametre (Gerekli sabit)
    mov         x3, #0                  // Dördüncü parametre
    
    mov         w8, #26                 // 🔥 ARM64 mimarisinde ptrace Sistem Çağrı Numarası (Syscall 26)
    svc         #0                      // ⚡ İŞLEMCİYE DİREKT EMİR: Çekirdek seviyesinde kilit at!

    // Not: Eğer arkadan sızan bir ajan (Frida/LLDB) varsa, kernel bu svc emriyle onu anında patlatır.
    ret                                 // Şasi temizse C++ dünyasına geri dön usta.

