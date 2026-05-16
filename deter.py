import sys

class DeterEngine:
    def __init__(self):
        self.hafiza = {}
        self.tipler = {}

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

                # --- Gelişmiş EĞER MANTIĞI (VE / VEYA Desteği) ---
                if satir.startswith("EGER"):
                    sart = satir.replace("EGER", "").strip()
                    
                    # Türkçe operatörleri Python'ın anlayacağı dile çeviriyoruz
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

        # ATAMA VE MATEMATİK
        elif "=" in satir:
            degisken, deger = satir.split("=")
            degisken, deger = degisken.strip(), deger.strip()
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
        # Sayı kontrolü (True/False boolean değerleri de desteklesin diye)
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
        
