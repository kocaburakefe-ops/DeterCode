import sys

class DeterBellek:
    def __init__(self):
        self.hafiza = {}
        self.tipler = {}
        self.torbalar = {}
        self.KIRMIZI = "\033[91m"
        self.SIFIRLA = "\033[0m"

    def degisken_kaydet(self, isim, deger, satir_no):
        if str(deger) in ["True", "False"]:
            tip = "MANTIK"
        else:
            tip = "SAYI" if str(deger).replace('.','',1).isdigit() else "YAZI"
            
        if isim in self.tipler and self.tipler[isim] != tip:
            print(f"\n{self.KIRMIZI}[DETER TİP HATASI] ({satir_no}): '{isim}' değişkeni {self.tipler[isim]} olarak kilitli! {tip} atayamazsın!{self.SIFIRLA}")
            sys.exit(1)
            
        self.tipler[isim] = tip
        self.hafiza[isim] = deger

    def torba_olustur(self, torba_adi):
        self.torbalar[torba_adi] = []
        self.tipler[torba_adi] = "TORBA"

    def torbaya_at(self, torba_adi, esya):
        if torba_adi in self.torbalar:
            self.torbalar[torba_adi].append(esya)

    def torbadan_sil(self, torba_adi, esya):
        if torba_adi in self.torbalar and esya in self.torbalar[torba_adi]:
            self.torbalar[torba_adi].remove(esya)
          
