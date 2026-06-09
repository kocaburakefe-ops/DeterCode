package com.kocaburakefe.detercode;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {

    // Bizim akıllı önbellek tankımız (RAM Deposu)
    private HashMap<String, String> memoryCache = new HashMap<>();

    static {
        System.loadLibrary("detercode_native");
    }

    public native String stringFromJNI();
    public native String getAsyncData(); // C++'taki yeni asenkron metoda bağlanan köprü

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Marşa basıyoruz ve akıllı pompayı test ediyoruz
        loadEngineData();
    }

    // Akıllı Önbellek ve Pompa Kontrol Merkezi
    private void loadEngineData() {
        String cacheKey = "fuel_status";

        // 1. Önce depoyu (Önbelleği) kontrol et
        if (memoryCache.containsKey(cacheKey)) {
            // Eğer veri zaten varsa hiç motoru yorma, direkt depodan ver
            String cachedData = memoryCache.get(cacheKey);
            // Hızlı teslimat!
        } else {
            // 2. Depo boşsa, arka plandaki C++ asenkron yakıt pompasını çalıştır
            new Thread(new Runnable() {
                @Override
                public void run() {
                    // C++ arka planda 2 saniye çalışır ama arayüzü asla kasmaz!
                    final String freshData = getAsyncData();
                    
                    // Gelen taze veriyi hemen akıllı önbelleğe (depoya) atıyoruz
                    memoryCache.put(cacheKey, freshData);
                    
                    // İşlem bittiğinde ekranda veya logda gösterebilirsin
                }
            }).start();
        }
    }
}

