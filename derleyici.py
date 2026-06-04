import sys

class DeterDerleyici:
    def __init__(self):
        self.SARI = "\033[93m"
        self.KIRMIZI = "\033[91m"
        self.YESIL = "\033[92m"
        self.SIFIRLA = "\033[0m"

    def statik_analiz_yap(self, satirlar_veri):
        print(f"{self.SARI}[ÖN DERLEME]: DeterCode statik tip kontrolleri yapılıyor...{self.SIFIRLA}")
        gecici_tipler = {}
        
        for satir, satir_no in satirlar_veri:
            if satir.startswith("DAHİL_ET") or satir.startswith("YETENEK") or satir == "YETENEK_BITIR":
                continue
                
            if "=" in satir and "sor" not in satir and "sansli_sayi" not in satir:
                parcalar = satir.split("=")
                var_name = parcalar[0].strip()
                val_expr = parcalar[1].strip()
                
                if val_expr.startswith('"') and val_expr.endswith('"'):
                    tahmini_tip = "YAZI"
                elif val_expr.replace('.','',1).isdigit():
                    tahmini_tip = "SAYI"
                elif val_expr in ["True", "False"]:
                    tahmini_tip = "MANTIK"
                else:
                    continue 
                
                if var_name in gecici_tipler and gecici_tipler[var_name] != tahmini_tip:
                    print(f"{self.KIRMIZI}\n[💥 STATİK DERLEME HATASI] ({satir_no}):")
                    print(f"-> '{var_name}' değişkeni zaten kilitli bir {gecici_tipler[var_name]} tipinde.")
                    print(f"-> Kod çalışmadan önce satırı temizle kanka, {tahmini_tip} atayamazsın!{self.SIFIRLA}")
                    sys.exit(1)
                
                gecici_tipler[var_name] = tahmini_tip
        print(f"{self.YESIL}[DERLEME BAŞARILI]: Sıfır amelelik, tam güvenlik!{self.SIFIRLA}\n")
      
