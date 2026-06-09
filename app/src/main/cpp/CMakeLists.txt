cmake_minimum_required(VERSION 3.22.1)

# Projemizin C++ motoruna isim veriyoruz
project("detercode_native")

# Bizim yazdığımız native-lib.cpp dosyasını bir kütüphane olarak derlemesini söylüyoruz
add_library(
        detercode_native
        SHARED
        native-lib.cpp)

# Android'in kendi sistem log kütüphanesini bağlıyoruz ki C++ içinden log basabilelim
find_library(
        log-lib
        log)

target_link_libraries(
        detercode_native
        ${log-lib})
        
