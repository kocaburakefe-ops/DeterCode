# -*- coding: utf-8 -*-
import os
import sys

def check_system_integrity():
    print("[Python Şefi]: Labirent kontrolü başlatıldı...")
    
    # Bizim o gizli labirentteki dosyaların yerinde olup olmadığını yukarıdan denetliyoruz
    cpp_path = "app/src/main/cpp/native-lib.cpp"
    asm_path = "app/src/main/cpp/asm_core/arm64_injector.S"
    
    if os.path.exists(cpp_path) and os.path.exists(asm_path):
        print("[Python Şefi]: ONAY - C++ motoru ve Saf Assembly odası yerli yerinde.")
        return True
    else:
        print("[Python Şefi]: HATA - Labirentte eksik parça var! Kabloları kontrol et usta.")
        return False

def main():
    print("====================================================")
    print(" DETERCODE KULE OTOMASYONU v1.0")
    print("====================================================")
    
    # Sistem kontrolünü çalıştırıyoruz
    if check_system_integrity():
        print("[Python Şefi]: Stage modları ve canlı gösterge paneli için akım veriliyor.")
        print("[Python Şefi]: Bulut işçilerine emir verildi: DERLEMEYE GEÇİN!")
        # Eğer her şey tamamsa bulut derleyicisine yeşil ışık yakıyoruz (Exit code 0)
        sys.exit(0)
    else:
        # Eksik varsa derlemeyi durdurup sigortayı attırıyoruz (Exit code 1)
        sys.exit(1)

if __name__ == "__main__":
    main()
  
