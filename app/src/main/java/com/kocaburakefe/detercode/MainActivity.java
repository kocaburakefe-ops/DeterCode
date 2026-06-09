package com.kocaburakefe.detercode;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // Uygulama ilk açıldığında C++ motorunu RAM'e yükleyen statik blok
    static {
        System.loadLibrary("detercode_native");
    }

    // C++ tarafındaki koda doğrudan bağlanan köprü fonksiyonumuz
    public native String stringFromJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // C++ motorundan gelen saf veri burada rölantide bekliyor
        // String motorMesaji = stringFromJNI();
    }
}

