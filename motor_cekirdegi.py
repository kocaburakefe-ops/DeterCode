import os
import time

class DeterCodeMotoru:
    def __init__(self):
        # KÜRESEL BELLEK
        self.bellek = {
            "kahraman_can": 60,       # Test için canı 60 yaptık (80'den küçük)
            "kahraman_max_can": 100,
            "kahraman_xp": 0,
            "kahraman_seviye": 1,
            "dusman_can": 150
        }
        self.kutuphaneler = []
        self.satir_atla = False # Karar mekanizmasının tetikçisi

    def ekrani_temizle(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def degiskenleri_coz(self, metin):
        for anahtar, deger in self.bellek.items():
            if anahtar in metin:
                metin = metin.replace(anahtar, str(deger))
        return metin

    def dosyaya_yaz(self, dosya_adi, icerik):
        icerik = self.degiskenleri_coz(icerik)
        with open(dosya_adi, "a", encoding="utf-8") as dosya:
            dosya.write(icerik + "\n")

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
                    print(f"[BELLEK GÜNCELLENDİ] {degisken_adi} -> {yeni_deger}")
                else:
                    print(f"[ÇEKİRDEK UYARISI] '{degisken_adi}' için geçersiz veri tipi!")
            except Exception as e:
                print(f"[ÇÖKME ENGELLENDİ] Matematik hatası savuşturuldu: {satir}")

    def satiri_isle(self, satir):
        satir = satir.strip()
        
        # Boş satırları ve yorumları direkt geç (atlama hakkını harcamasın)
        if not satir or satir.startswith("//"):
            return

        # EĞER ŞART SAĞLANMADIYSA BU SATIRI ATLA
        if self.satir_atla:
            self.satir_atla = False # Kilidi sıfırla
            print(f"[MANTIK] Şart sağlanmadığı için bu satır çalıştırılmadı: '{satir}'")
            return

        if satir.startswith("DAHİL_ET"):
            dosya_yolu = satir.split(" ")[1]
            if dosya_yolu not in self.kutuphaneler:
                self.kutuphaneler.append(dosya_yolu)
                print(f"[SİSTEM] {dosya_yolu} çekirdeğe kaynaklandı.")
                self.dosya_calistir(dosya_yolu)

        elif satir == "ekrani_temle":
            self.ekrani_temizle()

        elif satir.startswith("yazdir"):
            mesaj = satir.replace("yazdir", "").strip().replace('"', '')
            mesaj = self.degiskenleri_coz(mesaj)
            print(mesaj)

        # GERÇEK AKILLI MANTIK KONTROLÜ
        elif satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            sart_cozulmus = self.degiskenleri_coz(sart)
            try:
                sonuc = eval(sart_cozulmus)
                if sonuc:
                    print(f"[MANTIK] Şart DOĞRU: {sart} -> Alt satır tetiklenecek.")
                    self.satir_atla = False
                else:
                    print(f"[MANTIK] Şart YANLIŞ: {sart} -> Alt satır İPTAL edildi.")
                    self.satir_atla = True # Bir sonraki komut satırını atla emirini ver
            except Exception:
                print(f"[MANTIK HATASI] Şart çözülemedi, güvenlik amacıyla alt satır iptal: {sart}")
                self.satir_atla = True

        elif satir.startswith("yetenek_cagir"):
            parcalar = satir.split(" ")
            yetenek_adi = parcalar[1]
            print(f"[YETENEK ATEŞLENDİ] ===> {yetenek_adi.upper()} <===")

        elif "=" in satir and "EGER" not in satir:
            self.matematik_isleme(satir)

    def dosya_calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                satirlar = dosya.readlines()
                for satir in satirlar:
                    self.satiri_isle(satir)
        except FileNotFoundError:
            print(f"[FATAL ERROR] {dosya_yolu} bulunamadı!")

# --- MOTORU BAŞLATMA TESTİ ---
if __name__ == "__main__":
    motor = DeterCodeMotoru()
    print("========================================")
    print("   DETERCODE CORE V2.2 CONTROL FLOW")
    print("========================================")
    
    print("\n--- SİMÜLASYON BAŞLIYOR ---\n")
    motor.dosya_calistir("senaryolar/saf_guc.deter")
    
