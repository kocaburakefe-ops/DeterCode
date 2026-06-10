import time
import json

class TelemetryAnalyzer:
    def __init__(self):
        print("[DeterCar]: Python Telemetri Analizcisi devrede...")
        self.rpm_history = []

    def process_can_log(self, raw_data):
        """
        C++ tarafından gelen ham veriyi işler, anlamlı dataya dönüştürür.
        """
        try:
            # Burası simülasyon; gerçekte C++'tan gelen dosyayı okuruz
            raw_rpm = raw_data.get("rpm", 0)
            
            # Veri temizleme ve kalibrasyon
            if raw_rpm > 8000:
                print(f"[UYARI]: Anormal devir saptandı! {raw_rpm} RPM")
            
            self.rpm_history.append(raw_rpm)
            return {"status": "ok", "value": raw_rpm}
            
        except Exception as e:
            return {"status": "error", "message": str(e)}

    def generate_report(self):
        """Yapay zeka için analiz raporu oluşturur."""
        avg_rpm = sum(self.rpm_history) / len(self.rpm_history) if self.rpm_history else 0
        return f"Motorun ortalama çalışma devri: {avg_rpm:.2f} RPM"

# --- Simülasyon Testi ---
if __name__ == "__main__":
    analyzer = TelemetryAnalyzer()
    # Örnek bir veri akışı
    for i in range(5):
        data = {"rpm": 2000 + (i * 1000)}
        print(f"İşleniyor: {analyzer.process_can_log(data)}")
        time.sleep(0.5)
        
    print("-" * 30)
    print(analyzer.generate_report())
  
