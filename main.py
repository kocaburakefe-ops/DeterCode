from motor_cekirdegi import DeterCodeMotoru

def sistemi_ateşle():
    motor = DeterCodeMotoru()
    print("==================================================")
    print("      DETERCODE PROGRAMLAMA DİLİ - RUNTIME V3.0   ")
    print("==================================================")
    motor.dosya_calistir("senaryolar/saf_guc.deter")

if __name__ == "__main__":
    sistemi_ateşle()
    
