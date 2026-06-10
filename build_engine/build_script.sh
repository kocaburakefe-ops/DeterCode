#!/bin/bash

echo "--- DeterEngine: Montaj Hattı Başlatılıyor ---"

# Build klasörünün varlığını kontrol et
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# CMake haritasını çalıştır
echo "-> Haritalar okunuyor..."
cmake ..

# Derlemeyi başlat
echo "-> Motor parçaları birleştiriliyor..."
make

# Eğer hata yoksa çalıştır
if [ $? -eq 0 ]; then
    echo "-> Montaj Başarılı! Marşa basılıyor..."
    ./DeterEngine
else
    echo "-> [HATA]: Motor toplanamadı, parçaları kontrol et usta!"
fi

