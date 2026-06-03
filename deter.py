import sys
import random
import os
import time

class DeterEngine:
    def __init__(self):
        self.hafiza = {}
        self.tipler = {}
        self.torbalar = {}
        self.satirlar = []
        self.i = 0

    def calistir(self, dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as dosya:
                # Orijinal satırları ve gerçek satır numaralarını takip etmek için tuple listesi yapıyoruz
                self.satirlar = []
                for idx, s in enumerate(dosya, 1):
                    temiz_satir = s.strip()
                    if temiz_satir and not temiz_satir.startswith("//"):
                        self.satirlar.append((temiz_satir, idx))
                
            self.i = 0
            while self.i < len(self.satirlar):
                satir_veri, satir_no = self.satirlar[self.i]

                # --- TEKRARLA DÖNGÜSÜ ---
                if satir_veri.startswith("TEKRARLA"):
                    adet = int(satir_veri.split()[1])
                    dongu_satiri_veri, _ = self.satirlar[self.i + 1]
                    for _ in range(adet):
                        self.satir_isle(dongu_satiri_veri, satir_no)
                    self.i += 2
                    continue

                # --- YENİ: KENKEN DÖNGÜSÜ (WHILE) ---
                if satir_veri.startswith("KENKEN"):
                    sart = satir_veri.replace("KENKEN", "").strip()
                    sart = sart.replace(" VE ", " and ").replace(" VEYA ", " or ")
                    
                    dongu_satiri_veri, _ = self.satirlar[self.i + 1]
                    
                    # Şart sağlandığı sürece alttaki satırı çalıştır
                    while True:
                        gecerli_sart = sart
                        for var in self.hafiza:
                            if var in gecerli_sart:
                                gecerli_sart = gecerli_sart.replace(var, str(self.hafiza[var]))
                        
                        try:
                            if eval(gecerli_sart):
                                self.satir_isle(dongu_satiri_veri, satir_no + 1)
                            else:
                                break
                        except:
                            print(f"[DETER SÖZDİZİM HATASI] (Satır {satir_no}): '{sart}' şartı çözülemedi kanka.")
                            sys.exit()
                    self.i += 2
                    continue

                # --- EĞER MANTIĞI ---
                if satir_veri.startswith("EGER"):
                    sart = satir_veri.replace("EGER", "").strip()
                    sart = sart.replace(" VE ", " and ").replace(" VEYA ", " or ")
                    
                    if " HAS " in sart:
                        parcalar = sart.split(" HAS ")
                        torba_adi = parcalar[0].strip()
                        aranan_esya = parcalar[1].strip().replace('"', '')
                        
                        if torba_adi in self.torbalar:
                            durum = aranan_esya in self.torbalar[torba_adi]
                            sart = "True" if durum else "False"
                        else:
                            sart = "False"
                    else:
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
                        print(f"[DETER SÖZDİZİM HATASI] (Satır {satir_no}): '{sart}' şartı çözülemedi kanka.")
                        sys.exit()

                self.satir_isle(satir_veri, satir_no)
                self.i += 1
        except Exception as e:
            print(f"DETER SİSTEM HATASI: {e}")

    def satir_isle(self, satir, satir_no):
        if satir == "ekrani_temizle":
            os.system('cls' if os.name == 'nt' else 'clear')
            return

        if satir == "oyunu_bitir":
            print("\n===============================")
            print("       [ GAME OVER ]")
            print("  DeterCode Oyunu Sona Erdi!")
            print("===============================\n")
            sys.exit()

        if satir.startswith("bekle"):
            saniye = float(satir.split()[1])
            time.sleep(saniye)
            return

        if satir.startswith("hasar_ver"):
            parcalar = satir.split()
            degisken = parcalar[1]
            miktar = int(parcalar[2])
            if degisken in self.hafiza:
                self.hafiza[degisken] = int(self.hafiza[degisken]) - miktar
            else:
                print(f"[DETER MANTIKSAL HATA] (Satır {satir_no}): Hasar verilecek '{degisken}' bulunamadı kanka!")
            return

        if satir.startswith("iyilestir"):
            parcalar = satir.split()
            degisken = parcalar[1]
            miktar = int(parcalar[2])
            if degisken in self.hafiza:
                self.hafiza[degisken] = int(self.hafiza[degisken]) + miktar
            else:
                print(f"[DETER MANTIKSAL HATA] (Satır {satir_no}): İyileştirilecek '{degisken}' bulunamadı kanka!")
            return

        # --- GÜVENLİKLİ TORBA (LİSTE) KOMUTLARI ---
        if satir.startswith("torba_olustur"):
            torba_adi = satir.split()[1]
            if torba_adi in self.tipler:
                print(f"\n[DETER TİP HATASI] (Satır {satir_no}): '{torba_adi}' zaten {self.tipler[torba_adi]} olarak kilitli, torba yapılamaz!")
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
            else:
                print(f"[DETER MANTIKSAL HATA] (Satır {satir_no}): '{torba_adi}' adında bir torba yok kanka!")
            return

        elif satir.startswith("torbadan_sil"):
            parcalar = satir.split()
            torba_adi = parcalar[1]
            esya = " ".join(parcalar[2:]).replace('"', '')
            if torba_adi in self.torbalar:
                if esya in self.torbalar[torba_adi]:
                    self.torbalar[torba_adi].remove(esya)
                else:
                    print(f"UYARI (Satır {satir_no}): Torbada '{esya}' bulunamadığı için silinemedi kanka.")
            else:
                print(f"[DETER MANTIKSAL HATA] (Satır {satir_no}): '{torba_adi}' adında bir torba yok kanka!")
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
            self.degisken_kaydet(degisken, input(f"{mesaj} "), satir_no)

        # ATAMA VE MATEMATİK
        elif "=" in satir:
            degisken, deger = satir.split("=")
            degisken, deger = degisken.strip(), deger.strip()
            
            if degisken in self.tipler and self.tipler[degisken] == "TORBA":
                print(f"\n[DETER TİP HATASI] (Satır {satir_no}): '{degisken}' bir TORBA (Liste) olarak kilitli! Düz değer atayamazsın kanka!")
                sys.exit()

            if "sansli_sayi" in deger:
                parcalar = deger.split("sansli_sayi")[1].split()
                min_deger, max_deger = int(parcalar[0]), int(parcalar[1])
                rastgele_sonuc = random.randint(min_deger, max_deger)
                self.degisken_kaydet(degisken, rastgele_sonuc, satir_no)
                return

            hesap = deger
            for var in self.hafiza:
                if var in hesap:
                    hesap = hesap.replace(var, str(self.hafiza[var]))
            try:
                if any(op in hesap for op in "+-*/<>=="):
                    sonuc = eval(hesap)
                    self.degisken_kaydet(degisken, sonuc, satir_no)
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
            print(f"\n[DETER TİP HATASI] (Satır {satir_no}): '{isim}' tipi {self.tipler[isim]} olarak kilitli!")
            sys.exit()
        self.tipler[isim], self.hafiza[isim] = tip, deger

if __name__ == "__main__":
    if len(sys.argv) > 1: DeterEngine().calistir(sys.argv[1])
        
