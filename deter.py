import sys
import random
import os
import time
import re

class DeterEngine:
    def __init__(self):
        self.hafiza = {}
        self.tipler = {}
        self.torbalar = {}
        self.yetenekler = {}  # Fonksiyonları (Yetenekleri) tutan sözlük
        self.satirlar_veri = []
        self.i = 0
        
        # Resmi Turkuaz ve Metalik Marka Renklerimiz
        self.renkler = {
            "KIRMIZI": "\033[91m",
            "YESIL": "\033[92m",
            "SARI": "\033[93m",
            "MAVI": "\033[94m",
            "TURKUAZ": "\033[96m",
            "SIFIRLA": "\033[0m"
        }

    def calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                kod_icerik = dosya.read()
            
            # 1. ADIM: Ön İşleme (Yorum satırlarını temizle ve blokları analiz et)
            temiz_kod = []
            orijinal_satirlar = kod_icerik.splitlines()
            
            for idx, s in enumerate(orijinal_satirlar, 1):
                s_temiz = s.strip()
                if s_temiz and not s_temiz.startswith("//"):
                    temiz_kod.append((s_temiz, idx))
            
            self.satirlar_veri = temiz_kod
            
            # 2. ADIM: Fonksiyonları (YETENEK) Önceden Tara ve Belleğe Al
            self.yetenekleri_tara()
            
            # 3. ADIM: Ana Program Akışını Başlat
            self.i = 0
            while self.i < len(self.satirlar_veri):
                satir, satir_no = self.satirlar_veri[self.i]
                
                # Eğer bir yetenek tanımına denk gelirsek, içeriğini atla (çünkü çağrılınca çalışacak)
                if satir.startswith("YETENEK"):
                    self.blok_atla("YETENEK_BITIR")
                    continue
                    
                self.satir_isle(satir, satir_no)
                self.i += 1
                
        except Exception as e:
            print(f"{self.renkler['KIRMIZI']}[DETER SİSTEM HATASI]: {e}{self.renkler['SIFIRLA']}")

    def yetenekleri_tara(self):
        idx = 0
        while idx < len(self.satirlar_veri):
            satir, satir_no = self.satirlar_veri[idx]
            if satir.startswith("YETENEK"):
                parcalar = satir.split()
                if len(parcalar) < 2:
                    print(f"{self.renkler['KIRMIZI']}[SÖZDİZİM HATASI] (Satır {satir_no}): YETENEK adı belirtilmemiş!{self.renkler['SIFIRLA']}")
                    sys.exit()
                
                yetenek_adi = parcalar[1]
                govde = []
                idx += 1
                
                while idx < len(self.satirlar_veri) and self.satirlar_veri[idx][0] != "YETENEK_BITIR":
                    govde.append(self.satirlar_veri[idx])
                    idx += 1
                
                if idx >= len(self.satirlar_veri):
                    print(f"{self.renkler['KIRMIZI']}[SÖZDİZİM HATASI] (Satır {satir_no}): YETENEK bloğu kapatılmamış! (YETENEK_BITIR eksik){self.renkler['SIFIRLA']}")
                    sys.exit()
                
                self.yetenekler[yetenek_adi] = govde
            idx += 1

    def blok_atla(self, bitis_kelimesi):
        derinlik = 1
        self.i += 1
        while self.i < len(self.satirlar_veri):
            satir, _ = self.satirlar_veri[self.i]
            if satir.startswith("EGER") or satir.startswith("KENKEN") or satir.startswith("YETENEK"):
                derinlik += 1
            if satir == bitis_kelimesi or (bitis_kelimesi == "BLOK_BITIR" and satir in ["DEGİLSE", "DEGİLSE_EGER"]):
                if derinlik == 1:
                    return
            if satir == "BLOK_BITIR" or satir == "YETENEK_BITIR":
                derinlik -= 1
            self.i += 1

    def sart_degerlendir(self, sart, satir_no):
        sart = sart.replace(" VE ", " and ").replace(" VEYA ", " or ")
        
        # HAS (Çanta Kontrolü) Mekanizması
        if " HAS " in sart:
            parcalar = sart.split(" HAS ")
            torba_adi = parcalar[0].strip()
            aranan_esya = parcalar[1].strip().replace('"', '')
            if torba_adi in self.torbalar:
                return aranan_esya in self.torbalar[torba_adi]
            return False
            
        # Değişkenleri yerine koyma
        gecerli_sart = sart
        for var in sorted(self.hafiza.keys(), key=len, reverse=True):
            if var in gecerli_sart:
                gecerli_sart = re.sub(r'\b' + var + r'\b', str(self.hafiza[var]), gecerli_sart)
        
        try:
            return bool(eval(gecerli_sart))
        except:
            print(f"{self.renkler['KIRMIZI']}[DETER SÖZDİZİM HATASI] (Satır {satir_no}): '{sart}' şartı çözülemedi kanka.{self.renkler['SIFIRLA']}")
            sys.exit()

    def satir_isle(self, satir, satir_no):
        # 1. HUD VE EKRAN KOMUTLARI
        if satir == "ekrani_temizle":
            os.system('cls' if os.name == 'nt' else 'clear')
            return

        if satir.startswith("hud_ciz"):
            parcalar = satir.split()
            can_degisken = parcalar[1]
            if can_degisken in self.hafiza:
                val = int(self.hafiza[can_degisken])
                bar = "█" * (val // 10) + "░" * (10 - (val // 10))
                print(f"{self.renkler['TURKUAZ']}╔══════════════════════════════════════╗")
                print(f"║ CAN: [{bar}] %{val}              ║")
                print(f"╚══════════════════════════════════════╝{self.renkler['SIFIRLA']}")
            return

        if satir == "oyunu_bitir":
            print(f"\n{self.renkler['KIRMIZI']}===============================")
            print("       [ GAME OVER ]")
            print("  DeterCode v15.0 Kapanıyor.")
            print(f"===============================\n{self.renkler['SIFIRLA']}")
            sys.exit()

        if satir.startswith("bekle"):
            time.sleep(float(satir.split()[1]))
            return

        # 2. Gelişmiş EGER / DEGİLSE_EGER / DEGİLSE Blok Yapısı
        if satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            sonuc = self.sart_degerlendir(sart, satir_no)
            
            if sonuc:
                # Şart doğru, bir sonraki satıra geç ve çalıştır
                return
            else:
                # Şart yanlış, bir sonraki blok kırılımına kadar atla
                self.i += 1
                while self.i < len(self.satirlar_veri):
                    akt_satir, akt_no = self.satirlar_veri[self.i]
                    if akt_satir.startswith("DEGİLSE_EGER"):
                        yeni_sart = akt_satir.replace("DEGİLSE_EGER", "").strip()
                        if self.sart_degerlendir(yeni_sart, akt_no):
                            return
                    elif akt_satir == "DEGİLSE":
                        return
                    elif akt_satir == "BLOK_BITIR":
                        return
                    elif akt_satir.startswith("EGER") or akt_satir.startswith("KENKEN"):
                        self.blok_atla("BLOK_BITIR")
                    self.i += 1
                return

        if satir.startswith("DEGİLSE_EGER") or satir == "DEGİLSE":
            # Eğer halihazırda doğru bir bloğun içinden çıkıp buraya geldiysek, bloğun kalanını tamamen atla
            self.blok_atla("BLOK_BITIR")
            return

        if satir == "BLOK_BITIR":
            return

        # 3. KENKEN (DÖNGÜ) MANTIĞI
        if satir.startswith("KENKEN"):
            sart = satir.replace("KENKEN", "").strip()
            baslangic_i = self.i
            
            while self.sart_degerlendir(sart, satir_no):
                self.i = baslangic_i + 1
                while self.i < len(self.satirlar_veri) and self.satirlar_veri[self.i][0] != "BLOK_BITIR":
                    akt_satir, akt_no = self.satirlar_veri[self.i]
                    self.satir_isle(akt_satir, akt_no)
                    self.i += 1
            
            self.i = baslangic_i
            self.blok_atla("BLOK_BITIR")
            return

        # 4. YETENEK ÇAĞIRMA (FONKSİYONLAR)
        if satir.startswith("yetenek_cagir"):
            y_adi = satir.split()[1]
            if y_adi in self.yetenekler:
                eski_i = self.i
                for g_satir, g_no in self.yetenekler[y_adi]:
                    self.satir_isle(g_satir, g_no)
                self.i = eski_i
            else:
                print(f"{self.renkler['KIRMIZI']}[MANTIKSAL HATA] (Satır {satir_no}): '{y_adi}' adında bir yetenek bulunamadı kanka!{self.renkler['SIFIRLA']}")
            return

        # 5. OYUN MEKANİKLERİ VE HASAR SİSTEMİ
        if satir.startswith("hasar_ver"):
            parcalar = satir.split()
            degisken, miktar = parcalar[1], int(parcalar[2])
            if degisken in self.hafiza:
                self.hafiza[degisken] = int(self.hafiza[degisken]) - miktar
            return

        if satir.startswith("iyilestir"):
            parcalar = satir.split()
            degisken, miktar = parcalar[1], int(parcalar[2])
            if degisken in self.hafiza:
                self.hafiza[degisken] = int(self.hafiza[degisken]) + miktar
            return

        # 6. ENVENTER / MATRİS İŞLEMLERİ
        if satir.startswith("torba_olustur"):
            torba_adi = satir.split()[1]
            if torba_adi in self.tipler:
                print(f"\n{self.renkler['KIRMIZI']}[DETER TİP HATASI]: '{torba_adi}' kilitli!{self.renkler['SIFIRLA']}")
                sys.exit()
            self.torbalar[torba_adi] = []
            self.tipler[torba_adi] = "TORBA"
            return

        elif satir.startswith("torbaya_at"):
            parcalar = satir.split()
            torba_adi = parcalar[1]
            esya = " ".join(parcalar[2:]).replace('"', '')
            if torba_adi in self.torbalar:
                self.torbalar[torba_adi].append(esya)
            return

        elif satir.startswith("torbadan_sil"):
            parcalar = satir.split()
            torba_adi = parcalar[1]
            esya = " ".join(parcalar[2:]).replace('"', '')
            if torba_adi in self.torbalar and esya in self.torbalar[torba_adi]:
                self.torbalar[torba_adi].remove(esya)
            return

        elif satir.startswith("torbadan_goster"):
            torba_adi = satir.split()[1]
            if torba_adi in self.torbalar:
                print(f"{self.renkler['TURKUAZ']}[{torba_adi.upper()}]: {', '.join(self.torbalar[torba_adi])}{self.renkler['SIFIRLA']}")
            return

        # 7. YAZDIRMA VE RENKLER
        if satir.startswith("renkli_yazdir"):
            parcalar = satir.split()
            renk = parcalar[1].upper()
            icerik = " ".join(parcalar[2:]).strip()
            metin = self.hafiza.get(icerik, icerik.replace('"', ''))
            print(f"{self.renkler.get(renk, '')}{metin}{self.renkler['SIFIRLA']}")
            return

        if satir.startswith("yazdir"):
            icerik = satir.replace("yazdir", "").strip()
            print(self.hafiza.get(icerik, icerik.replace('"', '')))
            return

        # 8. DEĞİŞKEN ATAMA VE SÖZDİZİMİ
        if "sor" in satir:
            degisken, mesaj = satir.split("sor")
            degisken = degisken.replace("=", "").strip()
            mesaj = mesaj.strip().replace('"', '')
            self.degisken_kaydet(degisken, input(f"{mesaj} "), satir_no)
            return

        if "=" in satir:
            degisken, deger = satir.split("=")
            degisken, deger = degisken.strip(), deger.strip()
            
            if degisken in self.tipler and self.tipler[degisken] == "TORBA":
                print(f"{self.renkler['KIRMIZI']}[DETER TİP HATASI]: '{degisken}' bir TORBA! Düz değer atanamaz!{self.renkler['SIFIRLA']}")
                sys.exit()

            if "sansli_sayi" in deger:
                parcalar = deger.split("sansli_sayi")[1].split()
                self.degisken_kaydet(degisken, random.randint(int(parcalar[0]), int(parcalar[1])), satir_no)
                return

            # Hesaplama alanı
            hesap = deger
            for var in self.hafiza:
                if var in hesap:
                    hesap = re.sub(r'\b' + var + r'\b', str(self.hafiza[var]), hesap)
            try:
                if any(op in hesap for op in "+-*/<>=="):
                    self.degisken_kaydet(degisken, eval(hesap), satir_no)
                else:
                    self.degisken_kaydet(degisken, deger.replace('"', ''), satir_no)
            except:
                self.degisken_kaydet(degisken, deger.replace('"', ''), satir_no)

    def degisken_kaydet(self, isim, deger, satir_no):
        if str(deger) in ["True", "False"]:
            tip = "MANTIK"
        else:
            tip = "SAYI" if str(deger).replace('.','',1).isdigit() else "YAZI"
            
        if isim in self.tipler and self.tipler[isim] != tip:
            print(f"\n{self.renkler['KIRMIZI']}[DETER TİP HATASI] (Satır {satir_no}): '{isim}' tipi {self.tipler[isim]} olarak kilitli!{self.renkler['SIFIRLA']}")
            sys.exit()
        self.tipler[isim], self.hafiza[isim] = tip, deger

if __name__ == "__main__":
    if len(sys.argv) > 1:
        DeterEngine().calistir(sys.argv[1])
        
