import os
import time

class DeterCodeMotoru:
    def __init__(self):
        # GELİŞMİŞ BELLEK YÖNETİMİ (Smart Memory)
        self.bellek = {
            "kahraman_can": 100,
            "kahraman_max_can": 100,
            "kahraman_xp": 0,
            "kahraman_seviye": 1,
            "dusman_can": 150
        }
        self.kutuphaneler = []

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
                # Python'un çökmesini engellemek için güvenli çalıştırma
                yeni_deger = eval(islem_cozulmus)
                
                # Tip Denetimi (Type Checking)
                if isinstance(yeni_deger, (int, float)):
                    self.bellek[degisken_adi] = yeni_deger
                    print(f"[BELLEK GÜNCELLENDİ] {degisken_adi} -> {yeni_deger}")
                else:
                    print(f"[ÇEKİRDEK UYARISI] '{degisken_adi}' değişkenine sayı olmayan bir veri atanmaya çalışıldı! İşlem reddedildi.")
                    
            except NameError:
                print(f"[ÇÖKME ENGELLENDİ] Hatalı değişken ismi kullanıldı: {satir}")
            except SyntaxError:
                print(f"[SÖZDİZİMİ HATASI] Matematiği yanlış yazdın reis: {satir}")
            except Exception as e:
                print(f"[BİLİNMEYEN ANOMALİ] {satir} -> Hata Kodu: {e}")

    def satiri_isle(self, satir):
        satir = satir.strip()
        
        if not satir or satir.startswith("//"):
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

        elif satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            sart_cozulmus = self.degiskenleri_coz(sart)
            try:
                sonuc = eval(sart_cozulmus)
                if sonuc:
                    print(f"[MANTIK OK] Şart sağlandı: {sart}")
                else:
                    print(f"[MANTIK ATLANDI] Şart sağlanmadı: {sart}")
            except Exception:
                print(f"[MANTIK HATASI] Şart anlaşılamadı: {sart}")

        elif satir.startswith("yetenek_cagir"):
            parcalar = satir.split(" ")
            yetenek_adi = parcalar[1]
            print(f"[YETENEK ATEŞLENDİ] ===> {yetenek_adi.upper()} <===")
            if len(parcalar) > 2:
                parametreler = parcalar[2:]
                print(f"[PARAMETRELER] {parametreler}")

        elif "=" in satir and "EGER" not in satir:
            self.matematik_isleme(satir)

    def dosya_calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                satirlar = dosya.readlines()
                for satir in satirlar:
                    self.satiri_isle(satir)
        except FileNotFoundError:
            print(f"[FATAL ERROR] {dosya_yolu} bulunamadı! Çekirdek eksik dosya ile başlatılamaz.")

    def durum_guncelle(self, degisken, yeni_deger):
        self.bellek[degisken] = yeni_deger

    def sistem_kontrol(self):
        gerekli_kutuphaneler = ["kutuphane/temel_hareketler.deter", "kutuphane/boss_ai.deter"]
        print("\n[ÇEKİRDEK] Sistem bütünlüğü doğrulanıyor...")
        for lib in gerekli_kutuphaneler:
            if lib in self.kutuphaneler:
                print(f"[MODÜL] {lib} -> AKTİF")
            else:
                print(f"[MODÜL] {lib} -> BEKLEMEDE")

# --- MOTORU BAŞLATMA TESTİ ---
if __name__ == "__main__":
    motor = DeterCodeMotoru()
    print("========================================")
    print("   DETERCODE CORE V2.1 INITIALIZED")
    print("========================================")
    
    motor.sistem_kontrol()
    
    # Zırh testini çalıştırıyoruz
    print("\n--- SİMÜLASYON BAŞLIYOR ---\n")
    motor.dosya_calistir("senaryolar/saf_guc.deter")
    
