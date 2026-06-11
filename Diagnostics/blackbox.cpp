int main() {
    // 1. Kara kutuyu çalıştırıyoruz
    BlackBox blackbox(100);

    // 2. Motorun her hareketini kutuya fısıldıyoruz
    blackbox.record(__FILE__, __LINE__, "DeterEngine marşa basildi.");
    
    // Diyelim ki 11. özellikteki hafıza havuzunu tetikliyoruz
    blackbox.record(__FILE__, __LINE__, "MemoryPool'dan 1024 bayt kapatilmaya çalisiliyor.");
    
    // ... Burada kodlar çalışıyor, çalışıyor ...
    
    // Farz edelim ki tam burada donanımsal bir hata oldu ve sistem çökmek üzere!
    blackbox.record(__FILE__, __LINE__, "KRİTİK HATA: Gaz kelebeği voltaj sinyali koptu!");

    // Telefon kararmadan veya sistem küt diye gitmeden önce tek hamlede kutuyu patlatıyoruz:
    blackbox.dump_and_rescue();

    return 0;
}

