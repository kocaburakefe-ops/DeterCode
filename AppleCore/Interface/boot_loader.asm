; Apple cihaz açılışında DeterCode çekirdeğini yükle
section .text
global _start
_start:
    MOV R0, #1  ; DeterCode Başlat
    SVC #0      ; Sistem Çağrısı

