import os
import time
import json
import random  # V4.0 ile eklenen şans çekirdeği

class DeterCodeMotoru:
    def __init__(self):
        self.bellek = {
            "kahraman_can": 100,
            "kahraman_max_can": 100,
            "kahraman_xp": 0,
            "kahraman_seviye": 1,
            "dusman_can": 150,
            "dusman_ofke": 0,
            "oyun_zorluk": 1,
            "ses_seviyesi": 80,
            "son_hasar": 0  # Yeni dinamik değişken
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
        if "=" in satir and "EGER" not in satir and "RASTELE" not in satir:
            parcalar = satir.split("=")
            degisken_adi = parcalar[0].strip()
            islem = parcalar[1].strip()
            islem_cozulmus = self.degiskenleri_coz(islem)
            
            try:
                yeni_deger = eval(islem_cozulmus)
                if isinstance(yeni_deger, (int, float)):
                    self.bellek[degisken_adi] = yeni_deger
                    self.log_yaz(f"[BELLEK GÜNCELLENDİ] {degisken_adi} -> {yeni_deger}")
            except Exception:
                # V4.0 Self-Healing: Çökmek yerine güvenli bir fallback ataması yapar
                self.bellek[degisken_adi] = 0
                self.log_yaz(f"[ANOMALİ YAKALANDI] '{satir}' hesaplanamadı! Güvenlik gereği 0 atandı.")

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
                self.log_yaz(f"[SİSTEM MODÜLÜ] {dosya_yolu} enjekte ediliyor...")
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
                self.log_yaz(f"[MANTIK ANOMALİSİ] Şart çözülemedi, satır atlanıyor: {sart}")
                self.satir_atla = True

        # V4.0 RASTELE MİMARİSİ (Kullanım: RASTELE son_hasar = 15-45)
        elif satir.startswith("RASTELE"):
            try:
                parcalar = satir.replace("RASTELE", "").strip().split("=")
                degisken_adi = parcalar[0].strip()
                aralik = parcalar[1].strip().split("-")
                
                min_deg = int(self.degiskenleri_coz(aralik[0].strip()))
                max_deg = int(self.degiskenleri_coz(aralik[1].strip()))
                
                rastgele_sonuc = random.randint(min_deg, max_deg)
                self.bellek[degisken_adi] = rastgele_sonuc
                self.log_yaz(f"[ZAR ATILDI] RASTELE {degisken_adi} -> {rastgele_sonuc} ({min_deg}-{max_deg} arası)")
            except Exception as e:
                self.log_yaz(f"[ŞANS HATASI] Rastgele sayı üretim şablonu hatalı: {satir} | {e}")

        elif satir.startswith("BEKLE"):
            saniye = float(satir.split(" ")[1])
            time.sleep(saniye)

        elif satir == "DURDUR":
            self.log_yaz("[KAPATMA] Çekirdek güvenli modda kapatılıyor.")
            exit(0)

        elif satir.startswith("GOTO"):
            hedef_etiket = satir.split(" ")[1]
            if hedef_etiket in self.etiketler:
                self.ip = self.etiketler[hedef_etiket]
            else:
                self.log_yaz(f"[MANTIK HATASI] Etiket bulunamadı: '{hedef_etiket}'")

        elif satir == "VERI_KAYDET":
            with open("kayit/save_data.json", "w", encoding="utf-8") as f:
                json.dump(self.bellek, f, indent=4)
            self.log_yaz("[DEPOLAMA] Karakter verileri JSON dosyasına mühürlendi.")

        elif satir == "VERI_YUKLE":
            try:
                with open("kayit/save_data.json", "r", encoding="utf-8") as f:
                    self.bellek.update(json.load(f))
                self.log_yaz("[DEPOLAMA] Kayıtlı veriler başarıyla belleğe geri yüklendi.")
            except FileNotFoundError:
                pass

        elif satir.startswith("yetenek_cagir"):
            yetenek_adi = satir.split(" ")[1]
            self.log_yaz(f"[YETENEK TETİKLENDİ] ===> {yetenek_adi.upper()} <===")

        elif "=" in satir and "EGER" not in satir and "RASTELE" not in satir:
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
            self.log_yaz(f"[FATAL ERROR] {dosya_yolu} bulunamadı!")
            
