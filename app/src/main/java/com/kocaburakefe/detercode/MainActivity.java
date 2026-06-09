package com.kocaburakefe.detercode;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import androidx.appcompat.app.AppCompatActivity;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {

    private HashMap<String, String> memoryCache = new HashMap<>();
    
    // Bizim saniyede 60 kez C++ kapısını çalacak olan o asenkron zamanlayıcı kablomuz
    private Handler dashboardHandler = new Handler(Looper.getMainLooper());
    private Runnable dashboardRunnable;

    static {
        System.loadLibrary("detercode_native");
    }

    public native String stringFromJNI();
    public native String getAsyncData(); 
    public native String getHardwareInfo();
    public native String stressTestCPU();
    public native String getLiveDashboardData(); // İŞTE YENİ ÇEKTİĞİMİZ CANLI VERİ KABLOSU!

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        loadEngineData();
        String hardwareStatus = getHardwareInfo();

        // ---------------------------------------------------------------------
        // ELEKTRİK TESİSATI: Saniyede 60 kez C++ motorundan canlı veri çeken hat
        // ---------------------------------------------------------------------
        dashboardRunnable = new Runnable() {
            @Override
            public void run() {
                // C++ kapısını çal, o anlık 3 veriyi (Çekirdek, Isı, RAM) tek paket olarak al
                String rawData = getLiveDashboardData();
                
                // Gelen paketi virgüllerinden ayırıp kablolara dağıtıyoruz usta
                String[] parts = rawData.split(",");
                if (parts.length == 3) {
                    String core = parts[0];
                    String temp = parts[1];
                    String ram  = parts[2];

                    // BURASI ÖNEMLİ: Yarın bir gün tasarlayacağımız o fütüristik kadranların
                    // ibrelerini tam olarak buradaki 'core, temp, ram' verileriyle oynatacağız!
                }

                // 16 milisaniye sonra (60 FPS hızında) bu döngüyü tekrar tetikle!
                dashboardHandler.postDelayed(this, 16);
            }
        };

        // Canlı gösterge panelinin şalterini kaldırıyoruz, akım başladı!
        dashboardHandler.post(dashboardRunnable);
    }

    private void loadEngineData() {
        String cacheKey = "fuel_status";
        if (memoryCache.containsKey(cacheKey)) {
            String cachedData = memoryCache.get(cacheKey);
        } else {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    final String freshData = getAsyncData();
                    memoryCache.put(cacheKey, freshData);
                }
            }).start();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Telefon kapanırken veya uygulama arkaya atılırken akımı kes ki akü bitmesin usta!
        dashboardHandler.removeCallbacks(dashboardRunnable);
    }
}
