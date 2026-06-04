import sys
import random
import os
import time
import re
import importlib

# Yeni modüllerimizi içeri çekiyoruz kral
from bellek import DeterBellek
from derleyici import DeterDerleyici

class DeterEngine:
    def __init__(self):
        self.bellek = DeterBellek()
        self.derleyici = DeterDerleyici()
        self.yetenekler = {}
        self.satirlar_veri = []
        self.i = 0
        self.dahil_edilenler = set()
        self.renkler = {
            "KIRMIZI": "\033[91m", "YESIL": "\033[92m", "SARI": "\033[93m",
            "MAVI": "\033[94m", "TURKUAZ": "\033[96m", "SIFIRLA": "\033[0m"
        }

    def calistir(self, dosya_yolu):
        print(f"{self.renkler['TURKUAZ']}[🔒 v17.0 MULTI-MODULE ENGINE RUNNING]{self.renkler['SIFIRLA']}\n")
        try:
            self.kod_yukle_ve_tara(dosya_yolu)
            
            # Derleme modülünü ateşle kanka
            self.derleyici.statik_analiz_yap(self.satirlar_veri)
            
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
        if dosya_yolu in self.dahil_edilenler: return
        self.dahil_edilenler.add(dosya_yolu)
        if not os.path.exists(dosya_yolu):
            print(f"{self.renkler['KIRMIZI']}[BAĞLANTI HATASI]: '{dosya_yolu}' yok!{self.renkler['SIFIRLA']}")
            sys.exit(1)
        with open(dosya_yolu, "r", encoding="utf-8") as d:
            icerik = d.read()
        yeni = []
        for idx, s in enumerate(icerik.splitlines(), 1):
            s_temiz = s.strip()
            if s_temiz and not s_temiz.startswith("//"):
                yeni.append((s_temiz, f"{dosya_yolu}:{idx}"))
        self.satirlar_veri = yeni + self.satirlar_veri
        self.yetenekleri_tara()

    def yetenekleri_tara(self):
        idx = 0
        while idx < len(self.satirlar_veri):
            satir, satir_no = self.satirlar_veri[idx]
            if satir.startswith("YETENEK"):
                parcalar = satir.split()
                y_adi = parcalar[1]
                govde = []
                tanim_satiri = satir
                idx += 1
                while idx < len(self.satirlar_veri) and self.satirlar_veri[idx][0] != "YETENEK_BITIR":
                    govde.append(self.satirlar_veri[idx])
                    idx += 1
                self.yetenekler[y_adi] = (govde, tanim_satiri)
            idx += 1

    def blok_atla(self, bitis):
        derinlik = 1; self.i += 1
        while self.i < len(self.satirlar_veri):
            satir, _ = self.satirlar_veri[self.i]
            if satir.startswith("EGER") or satir.startswith("KENKEN") or satir.startswith("YETENEK"): derinlik += 1
            if satir == bitis or (bitis == "BLOK_BITIR" and satir in ["DEGİLSE", "DEGİLSE_EGER"]):
                if derinlik == 1: return
            if satir in ["BLOK_BITIR", "YETENEK_BITIR"]: derinlik -= 1
            self.i += 1

    def satir_isle(self, satir, satir_no):
        if satir.startswith("DAHİL_ET"):
            h = satir.replace("DAHİL_ET", "").strip()
            if h.endswith(".deter"): self.kod_yukle_ve_tara(h)
            else: globals()[h] = importlib.import_module(h)
            return
        if satir == "ekrani_temizle": os.system('cls' if os.name == 'nt' else 'clear'); return
        if satir == "oyunu_bitir": sys.exit(0)
        if satir.startswith("bekle"): time.sleep(float(satir.split()[1])); return
        if satir.startswith("hud_ciz"):
            v = max(0, int(self.bellek.hafiza.get(satir.split()[1], 0)))
            print(f"{self.renkler['TURKUAZ']}CAN: [{'█'*(v//10) + '░'*(10-(v//10))}] %{v}{self.renkler['SIFIRLA']}"); return
        if satir.startswith("yetenek_cagir"):
            parcalar = satir.split(); y_adi = parcalar[1]; args = parcalar[2:]
            if y_adi in self.yetenekler:
                govde, tanim = self.yetenekler[y_adi]
                params = tanim.split()[2:]
                for p, a in zip(params, args):
                    val = self.bellek.hafiza.get(a, a.replace('"', ''))
                    self.bellek.degisken_kaydet(p, val, satir_no)
                eski_i = self.i
                for g_s, g_n in govde: self.satir_isle(g_s, g_n)
                self.i = eski_i
            return
        if satir.startswith("EGER"):
            s = satir.replace("EGER", "").strip()
            for v in self.bellek.hafiza: s = re.sub(r'\b'+v+r'\b', str(self.bellek.hafiza[v]), s)
            if eval(s): return
            self.blok_atla("BLOK_BITIR"); return
        if satir.startswith("KENKEN"):
            s = satir.replace("KENKEN", "").strip(); bas_i = self.i
            eval_s = s
            for v in self.bellek.hafiza: eval_s = re.sub(r'\b'+v+r'\b', str(self.bellek.hafiza[v]), eval_s)
            while eval(eval_s):
                self.i = bas_i + 1
                while self.i < len(self.satirlar_veri) and self.satirlar_veri[self.i][0] != "BLOK_BITIR":
                    self.satir_isle(self.satirlar_veri[self.i][0], self.satirlar_veri[self.i][1])
                    self.i += 1
                eval_s = s
                for v in self.bellek.hafiza: eval_s = re.sub(r'\b'+v+r'\b', str(self.bellek.hafiza[v]), eval_s)
            self.i = bas_i; self.blok_atla("BLOK_BITIR"); return
        if satir.startswith("hasar_ver") or satir.startswith("iyilestir"):
            p = satir.split(); d, m = p[1], int(self.bellek.hafiza.get(p[2], p[2]))
            if d in self.bellek.hafiza:
                self.bellek.hafiza[d] = (self.bellek.hafiza[d] - m) if "hasar" in p[0] else (self.bellek.hafiza[d] + m)
            return
        if satir.startswith("torba_olustur"): self.bellek.torba_olustur(satir.split()[1]); return
        if satir.startswith("torbaya_at"): self.bellek.torbaya_at(satir.split()[1], satir.split()[2].replace('"','')); return
        if satir.startswith("renkli_yazdir"):
            p = satir.split(); r = p[1].upper(); ic = " ".join(p[2:]).replace('"','')
            print(f"{self.renkler.get(r,'')}{self.bellek.hafiza.get(ic, ic)}{self.renkler['SIFIRLA']}"); return
        if satir.startswith("yazdir"):
            ic = satir.replace("yazdir","").strip().replace('"','')
            print(self.bellek.hafiza.get(ic, ic)); return
        if "sor" in satir:
            d, m = satir.split("sor"); d = d.replace("=","").strip()
            self.bellek.degisken_kaydet(d, input(m.strip().replace('"',' ') + " "), satir_no); return
        if "=" in satir:
            d, v = satir.split("="); d, v = d.strip(), v.strip()
            if "sansli_sayi" in v:
                p = v.split(); self.bellek.degisken_kaydet(d, random.randint(int(p[1]), int(p[2])), satir_no); return
            for var in self.bellek.hafiza: v = re.sub(r'\b'+var+r'\b', str(self.bellek.hafiza[var]), v)
            try: self.bellek.degisken_kaydet(d, eval(v), satir_no)
            except: self.bellek.degisken_kaydet(d, v.replace('"',''), satir_no)

if __name__ == "__main__":
    if len(sys.argv) > 1: DeterEngine().calistir(sys.argv[1])
            
