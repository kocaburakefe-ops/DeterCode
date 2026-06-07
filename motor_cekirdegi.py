import os
import time
import json
import random

class DeterCodeMotoru:
    def __init__(self):
        self.bellek = {
            "kahraman_can": 100,
            "kahraman_max_can": 100,
            "kahraman_hasar": 30,
            "dusman_can": 200,
            "dusman_max_can": 200,
            "dusman_hamlesi": 0, # AI'ın karar kodu
            "secim": 0,          # Oyuncu girdisi için
            "son_hasar": 0
        }
        self.kutuphaneler = []
        self.satir_atla = False
        self.etiketler = {}
        self.current_lines = []
        self.ip = 0 

    def log_yaz(self, mesaj):
        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
        log_mesaji = f"[{timestamp}] {mesaj}\n"
        print(mesaj)
        try:
            with open("logs/debug_log.txt", "a", encoding="utf-8") as f:
                f.write(log_mesaji)
        except FileNotFoundError:
            pass

    def degiskenleri_coz(self, metin):
        for anahtar, deger in self.bellek.items():
            if anahtar in metin:
                metin = metin.replace(anahtar, str(deger))
        return metin

    def matematik_isleme(self, satir):
        if "=" in satir and not any(k in satir for k in ["EGER", "RASTELE", "GIRDI"]):
            parcalar = satir.split("=")
            degisken_adi = parcalar[0].strip()
            islem = parcalar[1].strip()
            islem_cozulmus = self.degiskenleri_coz(islem)
            
            try:
                yeni_deger = eval(islem_cozulmus)
                if isinstance(yeni_deger, (int, float)):
                    self.bellek[degisken_adi] = yeni_deger
                    self.log_yaz(f"[BELLEK] {degisken_adi} -> {yeni_deger}")
            except Exception:
                self.bellek[degisken_adi] = 0
                self.log_yaz(f"[ANOMALİ] '{satir}' sıfırlandı.")

    def satiri_isle(self, satir):
        satir = satir.strip()
        
        if not satir or satir.startswith("//") or satir.startswith("ETİKET"):
            return

        if self.satir_atla:
            self.satir_atla = False
            return

        if satir.startswith("DAHİL_ET"):
            dosya_yolu = satir.split(" ")[1]
            if dosya_yolu not in self.kutuphaneler:
                self.kutuphaneler.append(dosya_yolu)
                self.log_yaz(f"[MODÜL] {dosya_yolu} yükleniyor...")
                alt_motor = DeterCodeMotoru()
                alt_motor.bellek = self.bellek
                alt_motor.dosya_calistir(dosya_yolu)
                self.bellek = alt_motor.bellek

        elif satir.startswith("yazdir"):
            mesaj = satir.replace("yazdir", "").strip().replace('"', '')
            mesaj = self.degiskenleri_coz(mesaj)
            self.log_yaz(mesaj)

        elif satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            sart_cozulmus = self.degiskenleri_coz(sart)
            try:
                if eval(sart_cozulmus):
                    self.satir_atla = False
                else:
                    self.satir_atla = True
            except Exception:
                self.satir_atla = True

        elif satir.startswith("RASTELE"):
            try:
                parcalar = satir.replace("RASTELE", "").strip().split("=")
                degisken_adi = parcalar[0].strip()
                aralik = parcalar[1].strip().split("-")
                min_deg = int(self.degiskenleri_coz(aralik[0].strip()))
                max_deg = int(self.degiskenleri_coz(aralik[1].strip()))
                rastgele_sonuc = random.randint(min_deg, max_deg)
                self.bellek[degisken_adi] = rastgele_sonuc
                self.log_yaz(f"[ZAR] RASTELE {degisken_adi} -> {rastgele_sonuc}")
            except Exception:
                pass

        # V5.0 DİNAMİK GİRDİ SİSTEMİ (Kullanım: GIRDI secim)
        elif satir.startswith("GIRDI"):
            degisken_adi = satir.split(" ")[1].strip()
            try:
                kullanici_girdisi = input(">> Seçiminiz: ")
                self.bellek[degisken_adi] = int(kullanici_girdisi)
            except ValueError:
                self.bellek[degisken_adi] = 0 # Geçersiz girdi koruması

        elif satir.startswith("BEKLE"):
            saniye = float(satir.split(" ")[1])
            time.sleep(saniye)

        elif satir == "DURDUR":
            self.log_yaz("[KAPATMA] Motor durduruldu.")
            exit(0)

        elif satir.startswith("GOTO"):
            hedef_etiket = satir.split(" ")[1]
            if hedef_etiket in self.etiketler:
                self.ip = self.etiketler[hedef_etiket]

        elif "=" in satir and not any(k in satir for k in ["EGER", "RASTELE", "GIRDI"]):
            self.matematik_isleme(satir)

    def dosya_calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                self.current_lines = [line.strip() for line in dosya.readlines()]
            
            for idx, line in enumerate(self.current_lines):
                if line.startswith("ETİKET"):
                    self.etiketler[line.split(" ")[1].strip()] = idx

            self.ip = 0
            while self.ip < len(self.current_lines):
                satir = self.current_lines[self.ip]
                self.ip += 1 
                self.satiri_isle(satir)
        except FileNotFoundError:
            self.log_yaz(f"[HATA] {dosya_yolu} yok!")
            
