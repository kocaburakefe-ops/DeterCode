from derleyici import DeterParser  # Senin mevcut derleyicin
from motor_cekirdegi import DeterCodeMotoru # Benim verdiğim çekirdek

def main():
    motor = DeterCodeMotoru()
    parser = DeterParser()
    
    print("--- DeterCode Engine v2.0 Başlatılıyor ---")
    
    # 1. Kod dosyasını yükle
    kod_dosyasi = "senaryolar/saf_guc.deter"
    
    # 2. Derleyici kodu oku ve komut listesine çevir
    komutlar = parser.oku(kod_dosyasi)
    
    # 3. Motor komutları tek tek işlesin
    for komut in komutlar:
        motor.satiri_isle(komut)
        
    print("--- Simülasyon Tamamlandı ---")

if __name__ == "__main__":
    main()
  
