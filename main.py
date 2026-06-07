from motor_cekirdegi import DeterCodeMotoru

def sistemi_ateşle():
    # Motoru başlat
    motor = DeterCodeMotoru()
    
    print("==================================================")
    # Burak ismi statik kalsın diye ekledik reis
    print("      DETERCODE PROGRAMLAMA DİLİ - RUNTIME V2.2   ")
    print("==================================================")
    
    # Ana senaryo dosyasını çalıştır
    motor.dosya_calistir("senaryolar/saf_guc.deter")

if __name__ == "__main__":
    sistemi_ateşle()
    
