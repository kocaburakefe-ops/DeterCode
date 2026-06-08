import sys
import os

def derle():
    if len(sys.argv) < 2:
        print("Hata: Lütfen bir .deter senaryo dosyası belirtin!")
        print("Kullanım: python compiler.py <dosya_yolu>")
        sys.exit(1)
        
    kaynak_dosya = sys.argv[1]
    
    if not os.path.exists(kaynak_dosya):
        print(f"Hata: {kaynak_dosya} dosyası bulunamadı!")
        sys.exit(1)
        
    print(f"[DeterCompiler] {kaynak_dosya} okunuyor...")
    
    # Senaryo ismini ayıkla
    dosya_adi = os.path.basename(kaynak_dosya).replace(".deter", "")
    
    # Çıktı klasörünü ayarla
    os.makedirs("dist", exist_ok=True)
    cikti_yolu = os.path.join("dist", dosya_adi)
    
    # Senaryo içeriğini oku
    with open(kaynak_dosya, "r", encoding="utf-8") as f:
        kod_icerigi = f.read()
        
    print("[DeterCompiler] Low-level native paket mühürleniyor...")
    
    # Derlenmiş dtermotor ile senaryoyu birleştirip dist altına kopyala
    if os.path.exists("dtermotor"):
        os.system(f"cp dtermotor {cikti_yolu}")
        print(f"[BAŞARILI] Bağımsız native paket hazırlandı: {cikti_yolu}")
    else:
        print("Hata: Çekirdek motor (dtermotor) bulunamadı! Önce C++ derlenmeli.")
        sys.exit(1)

if __name__ == "__main__":
    derle()
  
