import os
import time

class DeterCodeMotoru:
    def __init__(self):
        # KÜRESEL BELLEK (Oyunun Hafızası - Değişkenler burada yaşar)
        self.bellek = {
            "kahraman_can": 100,
            "kahraman_max_can": 100,
            "kahraman_xp": 0,
            "kahraman_seviye": 1,
            "dusman_can": 150
        }
        self.kutuphaneler = [] # Dahil edilen dosyaların listesi

    def ekrani_temizle(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def degiskenleri_coz(self, metin):
        # Metin içindeki değişken isimlerini bellekteki değerleriyle değiştirir
        for anahtar, deger in self.bellek.items():
            if anahtar in metin:
                metin = metin.replace(anahtar, str(deger))
        return metin

    def dosyaya_yaz(self, dosya_adi, icerik):
        # Log ve Save sisteminin arka planı
        icerik = self.degiskenleri_coz(icerik)
        with open(dosya_adi, "a", encoding="utf-8") as dosya:
            dosya.write(icerik + "\n")

    def matematik_isleme(self, satir):
        # Örn: kahraman_can = kahraman_can + 50
        if "=" in satir and "EGER" not in satir:
            parcalar = satir.split("=")
            degisken_adi = parcalar[0].strip()
            islem = parcalar[1].strip()
            
            # Değişkenleri sayılara çevir
            islem = self.degiskenleri_coz(islem)
            
            try:
                # Python'un eval gücünü kullanarak matematiği çözüyoruz
                yeni_deger = eval(islem)
                self.bellek[degisken_adi] = yeni_deger
            except Exception as e:
                print(f"[ÇEKİRDEK HATASI] Matematik işlemi başarısız: {satir}")

    def satiri_isle(self, satir):
        satir = satir.strip()
        
        # 1. Yorum Satırlarını ve Boşlukları Atla
        if not satir or satir.startswith("//"):
            return

        # 2. DAHİL_ET Komutu
        if satir.startswith("DAHİL_ET"):
            dosya_yolu = satir.split(" ")[1]
            if dosya_yolu not in self.kutuphaneler:
                self.kutuphaneler.append(dosya_yolu)
                print(f"[ÇEKİRDEK] {dosya_yolu} sisteme entegre edildi.")
                # Dahil edilen dosyayı hemen arka planda okuyup sisteme katıyoruz
                self.dosya_calistir(dosya_yolu)

        # 3. EKRANI TEMİZLE
        elif satir == "ekrani_temle":
            self.ekrani_temizle()

        # 4. YAZDIR Komutu
        elif satir.startswith("yazdir"):
            mesaj = satir.replace("yazdir", "").strip().replace('"', '')
            mesaj = self.degiskenleri_coz(mesaj)
            print(mesaj)

        # 5. EGER (IF) Mekanizması - Mantıksal Çekirdek
        elif satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            # Değişkenleri sayılara çevir (Örn: "100 <= 0")
            sart_cozulmus = self.degiskenleri_coz(sart)
            try:
                # Python'un işlemcisine soruyoruz: Bu şart doğru mu?
                sonuc = eval(sart_cozulmus)
                if sonuc:
                    print(f"[MANTIK] Şart sağlandı: {sart}")
                else:
                    print(f"[MANTIK] Şart sağlanmadı, atlanıyor: {sart}")
            except Exception as e:
                print(f"[MANTIK HATASI] Şart anlaşılamadı: {sart}")

        # 6. YETENEK ÇAĞIR (Fonksiyon Tetikleyici)
        elif satir.startswith("yetenek_cagir"):
            parcalar = satir.split(" ")
            yetenek_adi = parcalar[1]
            print(f"[SİSTEM] {yetenek_adi} yeteneği ateşleniyor...")
            
            # Parametreler varsa onları da yakala (Örn: kahraman_can dusman_can)
            if len(parcalar) > 2:
                parametreler = parcalar[2:]
                print(f"[SİSTEM] İletilen Veriler: {parametreler}")

        # 7. Matematik ve Atama işlemleri
        elif "=" in satir and "EGER" not in satir:
            self.matematik_isleme(satir)

    def dosya_calistir(self, dosya_yolu):
        # Ana çalıştırıcı fonksiyon
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                satirlar = dosya.readlines()
                for satir in satirlar:
                    self.satiri_isle(satir)
        except FileNotFoundError:
            print(f"[HATA] {dosya_yolu} bulunamadı!")

    # Belleği anlık güncelleyen "beyin sinyali"
    def durum_guncelle(self, degisken, yeni_deger):
        if degisken in self.bellek:
            self.bellek[degisken] = yeni_deger
            print(f"[BELLEK] {degisken} güncellendi: {yeni_deger}")
        else:
            self.bellek[degisken] = yeni_deger
            print(f"[BELLEK] Yeni değişken eklendi: {degisken} = {yeni_deger}")

    # Motorun tüm parçaları yerinde mi kontrolü
    def sistem_kontrol(self):
        # Yollar kütüphane klasörüne göre ayarlandı
        gerekli_kutuphaneler = ["kutuphane/temel_hareketler.deter", "kutuphane/boss_ai.deter", "kutuphane/hakem.deter"]
        print("[SİSTEM] Kontrol başlatılıyor...")
        for lib in gerekli_kutuphaneler:
            if lib in self.kutuphaneler:
                print(f"[TEST] {lib} - OK")
            else:
                print(f"[TEST] {lib} - BEKLENİYOR (Dosya çalışınca yüklenecek)")

# --- MOTORU BAŞLATMA TESTİ ---
if __name__ == "__main__":
    motor = DeterCodeMotoru()
    print("=== DeterCode Motoru Çekirdeği V2.0 Başlatıldı ===")
    
    # Motor kendi kendini test etsin
    motor.sistem_kontrol()
    
    # Ana dosyayı çalıştırarak sistemi ayaklandır
    motor.dosya_calistir("senaryolar/saf_guc.deter")
    
