import sys
import random
import os
import time
import re
import importlib

class DeterEngine:
    def __init__(self):
        self.hafiza = {}
        self.tipler = {}
        self.torbalar = {}
        self.yetenekler = {}  # format: {ad: (govde, tanim_satiri)}
        self.satirlar_veri = []
        self.i = 0
        self.dahil_edilenler = set()
        
        self.renkler = {
            "KIRMIZI": "\033[91m",
            "YESIL": "\033[92m",
            "SARI": "\033[93m",
            "MAVI": "\033[94m",
            "TURKUAZ": "\033[96m",
            "SIFIRLA": "\033[0m"
        }

    def calistir(self, dosya_yolu):
        print(f"{self.renkler['TURKUAZ']}")
        print("      ______   ______  ")
        print("     |  __  \ /  ____| ")
        print("     | |  |  |  /      ")
        print("     | |  |  | |   _⚔️_ ")
        print("     | |__|  |  \____| ")
        print("     |______/ \______| ")
        print("   [🔒 v17.0 ULTRA-CORE COMPILER]")
        print(f"{self.renkler['SIFIRLA']}\n")

        try:
            # 1. DOSYALARI YÜKLE VE BAĞLANTILARI TARA
            self.kod_yukle_ve_tara(dosya_yolu)
            
            # 2. C++ SEVİYESİ ÖN DERLEME VE STATİK TİP KONTROLÜ
            self.statik_on_derleme()
            
            # 3. ÇALIŞTIRMA AŞAMASI
            self.i = 0
            while self.i < len(self.satirlar_veri):
                satir, satir_no = self.satirlar_veri[self.i]
                
                if satir.startswith("YETENEK"):
                    self.blok_atla("YETENEK_BITIR")
                    continue
                    
                self.satir_isle(satir, satir_no)
                self.i += 1
                
        except Exception as e:
            print(f"{self.renkler['KIRMIZI']}[DETER SİSTEM HATASI]: {e}{self.renkler['SIFIRLA']}")

    def kod_yukle_ve_tara(self, dosya_yolu):
        if dosya_yolu in self.dahil_edilenler:
            return
        self.dahil_edilenler.add(dosya_yolu)

        if not os.path.exists(dosya_yolu):
            print(f"{self.renkler['KIRMIZI']}[BAĞLANTI HATASI]: '{dosya_yolu}' dosyası bulunamadı!{self.renkler['SIFIRLA']}")
            sys.exit(1)

        with open(dosya_yolu, "r", encoding="utf-8") as dosya:
            kod_icerik = dosya.read()
        
        yeni_satirlar = []
        for idx, s in enumerate(kod_icerik.splitlines(), 1):
            s_temiz = s.strip()
            if s_temiz and not s_temiz.startswith("//"):
                yeni_satirlar.append((s_temiz, f"{dosya_yolu}:{idx}"))
        
        self.satirlar_veri = yeni_satirlar + self.satirlar_veri
        self.yetenekleri_tara()

    def yetenekleri_tara(self):
        self.yetenekler = {}
        idx = 0
        while idx < len(self.satirlar_veri):
            satir, satir_no = self.satirlar_veri[idx]
            if satir.startswith("YETENEK"):
                parcalar = satir.split()
                if len(parcalar) < 2:
                    print(f"{self.renkler['KIRMIZI']}[SÖZDİZİM HATASI] ({satir_no}): YETENEK adı eksik!{self.renkler['SIFIRLA']}")
                    sys.exit(1)
                
                yetenek_adi = parcalar[1]
                govde = []
                tanim_satiri = satir
                idx += 1
                
                while idx < len(self.satirlar_veri) and self.satirlar_veri[idx][0] != "YETENEK_BITIR":
                    govde.append(self.satirlar_veri[idx])
                    idx += 1
                
                self.yetenekler[yetenek_adi] = (govde, tanim_satiri)
            idx += 1

    def statik_on_derleme(self):
        """ Kod çalışmadan önce C++ disipliniyle statik tip analizi yapar """
        print(f"{self.renkler['SARI']}[ÖN DERLEME]: DeterCode statik tip kontrolleri yapılıyor...{self.renkler['SIFIRLA']}")
        gecici_tipler = {}
        
        for satir, satir_no in self.satirlar_veri:
            if satir.startswith("DAHİL_ET") or satir.startswith("YETENEK") or satir == "YETENEK_BITIR":
                continue
                
            if "=" in satir and "sor" not in satir and "sansli_sayi" not in satir:
                parcalar = satir.split("=")
                var_name = parcalar[0].strip()
                val_expr = parcalar[1].strip()
                
                # Basit tip tahmini kanka
                if val_expr.startswith('"') and val_expr.endswith('"'):
                    tahmini_tip = "YAZI"
                elif val_expr.replace('.','',1).isdigit():
                    tahmini_tip = "SAYI"
                elif val_expr in ["True", "False"]:
                    tahmini_tip = "MANTIK"
                else:
                    continue # Dinamik hesaplamaları runtime'a bırak
                
                if var_name in gecici_tipler and gecici_tipler[var_name] != tahmini_tip:
                    print(f"{self.renkler['KIRMIZI']}\n[💥 STATİK DERLEME HATASI] ({satir_no}):")
                    print(f"-> '{var_name}' değişkeni zaten kilitli bir {gecici_tipler[var_name]} tipinde.")
                    print(f"-> Kod çalışmadan önce satırı temizle kanka, {tahmini_tip} atayamazsın!{self.renkler['SIFIRLA']}")
                    sys.exit(1)
                
                gecici_tipler[var_name] = tahmini_tip
        print(f"{self.renkler['YESIL']}[DERLEME BAŞARILI]: Sıfır amelelik, tam güvenlik! Motor ateşleniyor...\n{self.renkler['SIFIRLA']}")

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
        if " HAS " in sart:
            parcalar = sart.split(" HAS ")
            torba_adi = parcalar[0].strip()
            aranan_esya = parcalar[1].strip().replace('"', '')
            if torba_adi in self.torbalar:
                return aranan_esya in self.torbalar[torba_adi]
            return False
            
        gecerli_sart = sart
        for var in sorted(self.hafiza.keys(), key=len, reverse=True):
            if var in gecerli_sart:
                gecerli_sart = re.sub(r'\b' + var + r'\b', str(self.hafiza[var]), gecerli_sart)
        try:
            return bool(eval(gecerli_sart))
        except:
            print(f"{self.renkler['KIRMIZI']}[SÖZDİZİM HATASI] ({satir_no}): '{sart}' şartı çözülemedi.{self.renkler['SIFIRLA']}")
            sys.exit(1)

    def satir_isle(self, satir, satir_no):
        # 0. DAHİL_ET MEKANİZMASI
        if satir.startswith("DAHİL_ET"):
            hedef = satir.replace("DAHİL_ET", "").strip()
            if hedef.endswith(".deter"):
                self.kod_yukle_ve_tara(hedef)
                return
            else:
                try:
                    globals()[hedef] = importlib.import_module(hedef)
                    print(f"{self.renkler['MAVI']}[KÖPRÜ]: Python '{hedef}' içeri sızdırıldı.{self.renkler['SIFIRLA']}")
                except:
                    print(f"{self.renkler['KIRMIZI']}[KÖPRÜ HATASI] ({satir_no}): '{hedef}' yüklenemedi!{self.renkler['SIFIRLA']}")
                return

        if satir == "ekrani_temizle":
            os.system('cls' if os.name == 'nt' else 'clear')
            return

        if satir.startswith("hud_ciz"):
            parcalar = satir.split()
            can_degisken = parcalar[1]
            if can_degisken in self.hafiza:
                val = max(0, int(self.hafiza[can_degisken]))
                bar = "█" * (val // 10) + "░" * (10 - (val // 10))
                print(f"{self.renkler['TURKUAZ']}╔══════════════════════════════════════╗")
                print(f"║ CAN: [{bar}] %{val}              ║")
                print(f"╚══════════════════════════════════════╝{self.renkler['SIFIRLA']}")
            return

        if satir == "oyunu_bitir":
            print(f"\n{self.renkler['KIRMIZI']}[ GAME OVER ] DeterCode v17.0 Kapanıyor.{self.renkler['SIFIRLA']}")
            sys.exit(0)

        if satir.startswith("bekle"):
            time.sleep(float(satir.split()[1]))
            return

        # 1. PARAMETRELİ YETENEK ÇAĞIRMA (YENİ C++ GÜCÜ)
        if satir.startswith("yetenek_cagir"):
            parcalar = satir.split()
            y_adi = parcalar[1]
            gonderilen_argumanlar = parcalar[2:]
            
            if y_adi in self.yetenekler:
                govde, tanim_satiri = self.yetenekler[y_adi]
                tanim_parcalari = tanim_satiri.split()
                beklenen_parametreler = tanim_parcalari[2:]
                
                # Parametreleri ve argümanları eşle, lokal değişken ataması yap kanka
                for param, arg in zip(beklenen_parametreler, gonderilen_argumanlar):
                    deger = self.hafiza.get(arg, arg.replace('"', ''))
                    self.degisken_kaydet(param, deger, satir_no)
                
                eski_i = self.i
                for g_satir, g_no in govde:
                    self.satir_isle(g_satir, g_no)
                self.i = eski_i
            else:
                print(f"{self.renkler['KIRMIZI']}[MANTIKSAL HATA] ({satir_no}): '{y_adi}' bulunamadı!{self.renkler['SIFIRLA']}")
            return

        # 2. EGER / KENKEN BLOKLARI
        if satir.startswith("EGER"):
            sart = satir.replace("EGER", "").strip()
            if self.sart_degerlendir(sart, satir_no):
                return
            else:
                self.i += 1
                while self.i < len(self.satirlar_veri):
                    akt_satir, akt_no = self.satirlar_veri[self.i]
                    if akt_satir.startswith("DEGİLSE_EGER"):
                        if self.sart_degerlendir(akt_satir.replace("DEGİLSE_EGER", "").strip(), akt_no):
                            return
                    elif akt_satir == "DEGİLSE":
                        return
                    elif akt_satir == "BLOK_BITIR":
                        return
                    elif akt_satir.startswith("EGER") or akt_satir.startswith("KENKEN"):
                        self.blok_atla("BLOK_BITIR")
                    self.i += 1
                return

        if satir.startswith("DEGİLSE_EGER") or satir == "DEGİLSE" or satir == "BLOK_BITIR":
            self.blok_atla("BLOK_BITIR")
            return

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

        # 3. SAVAŞ MATEMATİĞİ VE SİSTEMLER
        if satir.startswith("hasar_ver"):
            parcalar = satir.split()
            degisken, miktar_str = parcalar[1], parcalar[2]
            miktar = int(self.hafiza.get(miktar_str, miktar_str))
            if degisken in self.hafiza:
                self.hafiza[degisken] = int(self.hafiza[degisken]) - miktar
            return

        if satir.startswith("iyilestir"):
            parcalar = satir.split()
            degisken, miktar_str = parcalar[1], parcalar[2]
            miktar = int(self.hafiza.get(miktar_str, miktar_str))
            if degisken in self.hafiza:
                self.hafiza[degisken] = int(self.hafiza[degisken]) + miktar
            return

        # 4. TORBA (ARRAY) SİSTEMLERİ
        if satir.startswith("torba_olustur"):
            torba_adi = satir.split()[1]
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

        # 5. EKRAN VE ATAMALAR
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

        if "sor" in satir:
            degisken, mesaj = satir.split("sor")
            degisken = degisken.replace("=", "").strip()
            mesaj = mesaj.strip().replace('"', '')
            self.degisken_kaydet(degisken, input(f"{mesaj} "), satir_no)
            return

        if "=" in satir:
            degisken, deger = satir.split("=")
            degisken, deger = degisken.strip(), deger.strip()
            
            if "sansli_sayi" in deger:
                parcalar = deger.split("sansli_sayi")[1].split()
                self.degisken_kaydet(degisken, random.randint(int(parcalar[0]), int(parcalar[1])), satir_no)
                return

            hesap = deger
            for var in self.hafiza:
                if var in hesap:
                    hesap = re.sub(r'\b' + var + r'\b', str(self.hafiza[var]), hesap)
            try:
                if any(op in hesap for op in "+-*/<>=."):
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
            print(f"\n{self.renkler['KIRMIZI']}[DETER TİP HATASI] ({satir_no}): '{isim}' değişkeni {self.tipler[isim]} olarak kilitli! {tip} atayamazsın!{self.renkler['SIFIRLA']}")
            sys.exit(1)
        self.tipler[isim], self.hafiza[isim] = tip, deger

if __name__ == "__main__":
    if len(sys.argv) > 1:
        DeterEngine().calistir(sys.argv[1])
                
