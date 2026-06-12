# ==========================================
# DETERENGINE SAFKAN MONTAJ HATTI (MAKEFILE)
# ==========================================

# Derleyici ve Saf Performans Bayrakları (C++20 Standartı)
CXX      = clang++
CXXFLAGS = -std=c++20 -O3 -Wall -Wextra -pthread -I./Core

# Çıktı Dosyasının Adı
TARGET   = DeterEngine

# Projedeki Tüm CPP Dosyalarını Otomatik Bulan Dedektör
SRCS     = main.cpp $(wildcard Core/*/*.cpp)
OBJS     = $(SRCS:.cpp=.o)

# Varsayılan Marş Basma Kuralı
all: $(TARGET)
	@echo "🌐 [DETERENGINE] 70 Silindirli Canavar Başarıyla Derlendi!"
	@echo "🏎️  Marşa basmak için: ./$(TARGET)"

# Bağlama (Linking) Aşaması - Parçaları Birleştirme
$(TARGET): $(OBJS)
	@echo "🔗 Parçalar birleştiriliyor, şasiye kaynak yapılıyor..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Derleme (Compilation) Aşaması - Her CPP'yi OBJ Dosyasına Çevirme
%.o: %.cpp
	@echo "⚙️  Derleniyor: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dükkan Temizliği (Eski Kalıntıları Silme)
clean:
	@echo "🧹 Tezgah temizleniyor, eski .o uzantılı çapaklar siliniyor..."
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

