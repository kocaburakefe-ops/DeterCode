package com.kocaburakefe.detercode;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {

    // Bizim akıllı önbellek tankımız (RAM Deposu)
    private HashMap<String, String> memoryCache = new HashMap<>();

    static {
        // Uygulama ilk açıldığında C++ motorunu RAM'e yükleyen statik blok
        System.loadLibrary("detercode_native");
    }

    // C++ tarafındaki kodlara doğrudan bağlanan köprü fonksiyonlarımız
    public native String stringFromJNI();
    public native String getAsyncData(); 
    public native String getHardwareInfo(); // 3. PAKET: C++ donanım köprüsüne bağlanan yeni hat

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // 2. PAKET: Marşa basıyoruz ve akıllı asenkron pompayı tetikliyoruz
        loadEngineData();

        // 3. PAKET: C++ seviyesinden gelen düşük seviye donanım analizini ateşliyoruz
        String hardwareStatus = getHardwareInfo();
        // Bu veri artık RAM'de; işlemci mimarisini ve toplam RAM'i direkt Linux çekirdeğinden okudu!
    }

    // Akıllı Önbellek ve Pompa Kontrol Merkezi (2. Paket)
    private void loadEngineData() {
        String cacheKey = "fuel_status";

        // 1. Önce depoyu (Önbelleği) kontrol et
        if (memoryCache.containsKey(cacheKey)) {
            // Eğer veri zaten varsa hiç motoru yorma, direkt depodan çek
            String cachedData = memoryCache.get(cacheKey);
        } else {
            // 2. Depo boşsa, arka plandaki C++ asenkron yakıt pompasını çalıştır
            new Thread(new Runnable() {
                @Override
                public void run() {
                    // C++ arka planda çalışırken telefonun arayüzü sıfır hararetle yağ gibi akar!
                    final String freshData = getAsyncData();
                    
                    // Gelen taze veriyi hemen akıllı önbelleğe (depoya) atıyoruz
                    memoryCache.put(cacheKey, freshData);
                }
            }).start();
        }
    }
}
