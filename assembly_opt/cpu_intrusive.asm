section .text
global fast_multiply_asm

; C++'dan gelen iki sayıyı çarpıp döndüren fonksiyon
fast_multiply_asm:
    mov rax, rdi    ; İlk parametreyi rax'e al
    imul rax, rsi   ; rax = rax * ikinci parametre (rsi)
    ret             ; Sonucu döndür

