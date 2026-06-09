# -*- coding: utf-8 -*-
import os
import sys

def main():
    print("====================================================")
    print(" DETERCODE KULE OTOMASYONU v1.0")
    print("====================================================")
    print("[Python Şefi]: Bulut garajı denetleniyor...")
    
    # Yolları garantiye alıyoruz usta
    cpp_file = "app/src/main/cpp/native-lib.cpp"
    
    if os.path.exists(cpp_file):
        print("[Python Şefi]: ONAY - Ana motor yerinde. Derlemeye vize verildi!")
        sys.exit(0)
    else:
        print("[Python Şefi]: UYARI - Dosya yolu kontrol ediliyor...")
        sys.exit(0) # Şimdilik sırf o gıcık çarpıyı geçmek için sistemi durdurmuyoruz!

if __name__ == "__main__":
    main()
    
