package com.kocaburakefe.detercode;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.widget.Button;   // Butonları sisteme tanıtmak için bu cıvatayı sıktık usta!
import android.widget.TextView; // Kaportadaki yazılara bağlanmak için bu cıvatayı ekledik!
import android.widget.Toast;    // Ekrana anlık bildirim fırlatmak için ekledik!
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

        // =====================================================================
        // PERFORMANS STAGE BUTONLARI BAĞLANTI TESİSATI (YENİ EKLEME)
        // =====================================================================
        Button btnStage0 = findViewById(R.id.btn_stage0);
        Button btnStage1 = findViewById(R.id.btn_stage1);
        Button btnStage2 = findViewById(R.id.btn_stage2);

        // STAGE 0: Rölanti (ECO) Modu Şalteri
        if (btnStage0 != null) {
            btnStage0.setOnClickListener(new android.view.View.OnClickListener() {
                @Override
                public void onClick(android.view.View view) {
                    Toast.makeText(MainActivity.this, "STAGE 0: MOTOR RÖLANTİDE (ECO)", Toast.LENGTH_SHORT).show();
                }
            });
        }

        // STAGE 1: Cadde (DENGELİ) Modu Şalteri
        if (btnStage1 != null) {
            btnStage1.setOnClickListener(new android.view.View.OnClickListener() {
                @Override
                public void onClick(android.view.View view) {
                    loadEngineData(); // Bizim akıllı bellek tankını doldur usta!
                    Toast.makeText(MainActivity.this, "STAGE 1: CADDE MODU AKTİF", Toast.LENGTH_SHORT).show();
                }
            });
        }

        // STAGE 2: Pist Modu - LİMİTÖR İPTALİ! 🏎️💨
        if (btnStage2 != null) {
            btnStage2.setOnClickListener(new android.view.View.OnClickListener() {
                @Override
                public void onClick(android.view.View view) {
                    // 5. Dil devrede! Kendi odasındaki saf Assembly (ASM) koduna düz kontak yapıyoruz!
                    int asmResult = triggerDirectAsm();
                    
                    // C++ stres testini ve çekirdek limitörlerini arka planda patlatıyoruz usta!
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            stressTestCPU();
                        }
                    }).start();

                    Toast.makeText(MainActivity.this, "STAGE 2: LİMİTÖR İPTAL EDİLDİ! ASM DEĞERİ: " + asmResult, Toast.LENGTH_LONG).show();
                }
            });
        }
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
