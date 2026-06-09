package com.kocaburakefe.detercode;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.widget.TextView; // Kaportadaki yazılara bağlanmak için bu cıvatayı ekledik!
import androidx.appcompat.app.AppCompatActivity;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {

    private HashMap<String, String> memoryCache = new HashMap<>();
    
    // Saniyede 60 kez C++ kapısını çalacak olan asenkron zamanlayıcı hattımız
    private Handler dashboardHandler = new Handler(Looper.getMainLooper());
    private Runnable dashboardRunnable;

    static {
        System.loadLibrary("detercode_native");
    }

    public native String stringFromJNI();
    public native String getAsyncData(); 
    public native String getHardwareInfo();
    public native String stressTestCPU();
    public native String getLiveDashboardData(); 
    
    // ---------------------------------------------------------------------
    // 5. DİLİN ŞALTERİ: Doğrudan İşlemci Hücrelerine (ASM) Düz Kontak Yapan Hat!
    // ---------------------------------------------------------------------
    public native int triggerDirectAsm(); 

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Önce senin oluşturduğun o fütüristik kaportayı (Layout) ekrana oturtuyoruz usta!
        setContentView(R.layout.activity_main);
        
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
                
                // Gelen paketi virgüllerinden ayırıp kablolara dağıtıyoruz
                final String[] parts = rawData.split(",");
                if (parts.length == 3) {
                    // Arayüzü kasmadan, o neon göstergeleri canlı oynatmak için güvenli hatta geçiyoruz
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            // Kabloları activity_main.xml'deki göstergelere tek tek bağlıyoruz usta!
                            TextView txtCore = findViewById(R.id.txt_active_core);
                            TextView txtTemp = findViewById(R.id.txt_temperature);
                            TextView txtRam = findViewById(R.id.txt_ram_usage);

                            if (txtCore != null) txtCore.setText("AKTİF ÇEKİRDEK: CORE #" + parts[0]);
                            if (txtTemp != null) txtTemp.setText("CPU HARARET: " + parts[1] + " °C");
                            if (txtRam != null)  txtRam.setText("RAM DEPO DOLULUK: %" + parts[2]);
                        }
                    });
                }

                // 16 milisaniye sonra (60 FPS hızında) bu döngüyü tekrar tetikle!
                dashboardHandler.postDelayed(this, 16);
            }
        };

        // Canlı gösterge panelinin şalterini kaldırıyoruz, akım başladı!
        dashboardHandler.post(dashboardRunnable);
        
        // ÖRNEK TEST: İleride butonlara bağlayacağımız o gizli Assembly silahını 
        // arka planda test etmek istersen şimdilik burası çalıştırıp sonucu donanımdan koparır:
        // int asmResult = triggerDirectAsm(); 
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
        // Uygulama kapanırken akımı kes ki akü bitmesin, kaçak elektrik kalmasın usta!
        dashboardHandler.removeCallbacks(dashboardRunnable);
    }
}
