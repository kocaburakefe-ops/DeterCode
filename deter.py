import sys
import random
import os
import time # Zamanı yavaşlatmak, bekletmek için Python'ın time modülünü bağlıyoruz

class DeterEngine:
    def __init__(self):
        self.hafiza = {}
        self.tipler = {}
        self.torbalar = {}

    def calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                self.satirlar = [s.strip() for s in dosya if s.strip() and not s.strip().startswith("//")]
                
            self.i = 0
            while self.i < len(self.satirlar):
                satir = self.satirlar[self.i]

                # --- TEKRARLA DÖNGÜSÜ ---
                if satir.startswith("TEKRARLA"):
                    adet = int(satir.split()[1])
                    dongu_satiri = self.satirlar[self.i + 1]
                    for _ in range(adet):
                        self.satir_isle(dongu_satiri)
                    self.i += 2
                    continue

                # --- EĞER MANTIĞI ---
                if satir.startswith("EGER"):
                    sart = satir.replace("EGER", "").strip()
                    sart = sart.replace(" VE ", " and ").replace(" VEYA ", " or ")
                    
                    for var in self.hafiza:
                        if var in sart:
                            sart = sart.replace(var, str(self.hafiza[var]))
                    
                    try:
                        if eval(sart):
                            self.i += 1
                            continue
                        else:
                            self.i += 2
                            continue
                    except:
                        print(f"HATA: '{sart}' şartı çözülemedi kanka.")
                        sys.exit()

                self.satir_isle(satir)
                self.i += 1
        except Exception as e:
            print(f"DETER SİSTEM HATASI: {e}")

    def satir_isle(self, satir):
        # --- EKRAN TEMİZLEME ---
        if satir == "ekrani_temizle":
            os.system('cls' if os.name == 'nt' else 'clear')
            return

        # --- YENİ: ZAMAN BEKLETME KOMUTU ---
        # Örn: bekle 2 (Sistemi 2 saniye boyunca durdurur)
        if satir.startswith("bekle"):
            saniye = float(satir.split()[1])
            time.sleep(saniye)
            return

        # --- TORBA (LİSTE) KOMUTLARI ---
        if satir.startswith("torba_olustur"):
            torba_adi = satir.split()[1]
            self.torbalar[torba_adi] = []
            return

        elif satir.startswith("torbaya_at"):
            parcalar = satir.split()
            torba_adi = parcalar[1]
            esya = " ".join(parcalar[2:]).replace('"', '')
            if torba_adi in self.torbalar:
                self.torbalar[torba_adi].append(esya)
            else:
                print(f"HATA: '{torba_adi}' adında bir torba yok kanka!")
            return

        elif satir.startswith("torbadan_goster"):
            torba_adi = satir.split()[1]
            if torba_adi in self.torbalar:
                print(f"[{torba_adi.upper()} İÇERİĞİ]: {', '.join(self.torbalar[torba_adi])}")
            return

        # YAZDIRMA
        if satir.startswith("yazdir"):
            icerik = satir.replace("yazdir", "").strip()
            print(self.hafiza.get(icerik, icerik.replace('"', '')))

        # SORU SORMA
        elif "sor" in satir:
            degisken, mesaj = satir.split("sor")
            degisken = degisken.replace("=", "").strip()
            mesaj = mesaj.strip().replace('"', '')
            self.degisken_kaydet(degisken, input(f"{mesaj} "))

        # ATAMA, MATEMATİK VE ŞANS
        elif "=" in satir:
            degisken, deger = satir.split("=")
            degisken, deger = degisken.strip(), deger.strip()
            
            if "sansli_sayi" in deger:
                parcalar = deger.split("sansli_sayi")[1].split()
                min_deger = int(parcalar[0])
                max_deger = int(parcalar[1])
                rastgele_sonuc = random.randint(min_deger, max_deger)
                self.degisken_kaydet(degisken, rastgele_sonuc)
                return

            hesap = deger
            for var in self.hafiza:
                if var in hesap:
                    hesap = hesap.replace(var, str(self.hafiza[var]))
            try:
                if any(op in hesap for op in "+-*/<>=="):
                    sonuc = eval(hesap)
                    self.degisken_kaydet(degisken, sonuc)
                else:
                    self.degisken_kaydet(degisken, deger.replace('"', ''))
            except:
                self.degisken_kaydet(degisken, deger.replace('"', ''))

    def degisken_kaydet(self, isim, deger):
        if str(deger) in ["True", "False"]:
            tip = "MANTIK"
        else:
            tip = "SAYI" if str(deger).replace('.','',1).isdigit() else "YAZI"
            
        if isim in self.tipler and self.tipler[isim] != tip:
            print(f"\n[DETER TİP HATASI]: '{isim}' tipi {self.tipler[isim]} olarak kilitli!")
            sys.exit()
        self.tipler[isim], self.hafiza[isim] = tip, deger

if __name__ == "__main__":
    if len(sys.argv) > 1: DeterEngine().calistir(sys.argv[1])
        
