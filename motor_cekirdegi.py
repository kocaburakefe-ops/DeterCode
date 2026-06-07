import os
import time
import json

class DeterCodeMotoru:
    def __init__(self):
        # MERKEZİ BELLEK MİMARİSİ
        self.bellek = {
            "kahraman_can": 100,
            "kahraman_max_can": 100,
            "kahraman_xp": 0,
            "kahraman_seviye": 1,
            "dusman_can": 150,
            "dusman_ofke": 0,
            "oyun_zorluk": 1,
            "ses_seviyesi": 80
        }
        self.kutuphaneler = []
        self.satir_atla = False
        
        # JUMP & LOOP MİMARİSİ (Instruction Pointer ve Etiketler)
        self.etiketler = {}
        self.current_lines = []
        self.ip = 0  # Instruction Pointer (Yönerge İşaretçisi)

    def log_yaz(self, mesaj):
        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
        log_mesaji = f"[{timestamp}] {mesaj}\n"
        print(mesaj)
        try:
            with open("logs/debug_log.txt", "a", encoding="utf-8") as f:
                f.write(log_mesaji)
        except FileNotFoundError:
            pass

    def ekrani_temizle(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def degiskenleri_coz(self, metin):
        for anahtar, deger in self.bellek.items():
            if anahtar in metin:
                metin = metin.replace(anahtar, str(deger))
        return metin

    def matematik_isleme(self, satir):
        if "=" in satir and "EGER" not in satir:
            parcalar = satir.split("=")
            degisken_adi = parcalar[0].strip()
            islem = parcalar[1].strip()
            islem_cozulmus = self.degiskenleri_coz(islem)
            
            try:
                yeni_deger = eval(islem_cozulmus)
                if isinstance(yeni_deger, (int, float)):
                    self.bellek[degisken_adi] = yeni_deger
                    self.log_yaz(f"[BELLEK GÜNCELLENDİ] {degisken_adi} -> {yeni_deger}")
                else:
                    self.log_yaz(f"[ÇEKİRDEK UYARISI] '{degisken_adi}' için geçersiz veri tipi!")
            except Exception:
                self.log_yaz(f"[ÇÖKME ENGELLENDİ] Hatalı matematik işlemi pas geçildi: {satir}")

    def satiri_isle(self, satir):
        satir = satir.strip()
        
        if not satir or satir.startswith("//") or satir.startswith("ETİKET"):
            return

        if self.satir_atla:
            self.satir_atla = False
            self.log_yaz(f"[MANTIK] Şart sağlanmadığı için satır atlandı: '{satir}'")
            return

        if satir.startswith("DAHİL_ET"):
            dosya_yolu = satir.split(" ")[1]
            if dosya_yolu not in self.kutuphaneler:
                self.kutuphaneler.append(dosya_yolu)
                self.log_yaz(f"[SİSTEM MODÜLÜ] {dosya_yolu} sisteme yükleniyor...")
                # Alt kütüphaneleri mevcut IP'yi bozmadan ayrı çalıştırır
                alt_motor = DeterCodeMotoru()
                alt_motor.bellek = self.bellek
                alt_motor.dosya_calistir(dosya_yolu)
                self.bellek = alt_motor.bellek

        elif satir == "ekrani_temle":
            self.ekrani_temizle()

        elif satir.startswith("yazdir"):
            mesaj = satir.replace("yazdir", "").strip().replace('"', '')
            mesaj = self.degiskenleri_coz(mesaj)
            self.log_yaz(mesaj)

        elif satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            sart_cozulmus = self.degiskenleri_coz(sart)
            try:
                if eval(sart_cozulmus):
                    self.log_yaz(f"[MANTIK] Şart DOĞRU: {sart}")
                    self.satir_atla = False
                else:
                    self.log_yaz(f"[MANTIK] Şart YANLIŞ: {sart}")
                    self.satir_atla = True
            except Exception:
                self.log_yaz(f"[MANTIK HATASI] Şart çözülemedi: {sart}")
                self.satir_atla = True

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
                self.log_yaz(f"[JUMP] Kod '{hedef_etiket}' etiketine sıçradı (Satır: {self.ip})")
            else:
                self.log_yaz(f"[JUMP ERROR] '{hedef_etiket}' adında bir etiket bulunamadı!")

        elif satir == "VERI_KAYDET":
            try:
                with open("kayit/save_data.json", "w", encoding="utf-8") as f:
                    json.dump(self.bellek, f, indent=4)
                self.log_yaz("[DEPOLAMA] Karakter verileri JSON dosyasına mühürlendi.")
            except Exception as e:
                self.log_yaz(f"[DEPOLAMA HATASI] Kayıt başarısız: {e}")

        elif satir == "VERI_YUKLE":
            try:
                with open("kayit/save_data.json", "r", encoding="utf-8") as f:
                    yuklenen_veri = json.load(f)
                    self.bellek.update(yuklenen_veri)
                self.log_yaz("[DEPOLAMA] Kayıtlı veriler başarıyla belleğe geri yüklendi.")
            except FileNotFoundError:
                self.log_yaz("[DEPOLAMA] Kayıt dosyası bulunamadı, varsayılan bellek aktif.")

        elif satir.startswith("yetenek_cagir"):
            yetenek_adi = satir.split(" ")[1]
            self.log_yaz(f"[YETENEK TETİKLENDİ] ===> {yetenek_adi.upper()} <===")

        elif "=" in satir and "EGER" not in satir:
            self.matematik_isleme(satir)

    def dosya_calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                self.current_lines = [line.strip() for line in dosya.readlines()]
            
            # ETİKETLERİ ÖNCEDEN TARA VE KAYDET (Pre-parsing Labels)
            for idx, line in enumerate(self.current_lines):
                if line.startswith("ETİKET"):
                    etiket_adi = line.split(" ")[1].strip()
                    self.etiketler[etiket_adi] = idx

            # INSTRUCTION POINTER DÖNGÜSÜ
            self.ip = 0
            while self.ip < len(self.current_lines):
                satir = self.current_lines[self.ip]
                self.ip += 1  # İşaretçiyi ilerlet
                self.satiri_isle(satir)
                
        except FileNotFoundError:
            self.log_yaz(f"[FATAL ERROR] {dosya_yolu} bulunamadı!")
            
