import SwiftUI

struct MacContentView: View {
    // Bizim ortak Objective-C++ köprüsünü MacBook işlemcisi için de çağırıyoruz usta
    let bridge = DeterEngineBridge()
    
    // Canlı terminal raporu metni
    @State private var terminalLog: String = "DeterEngine macOS Çekirdek Sistem Kontrolü Aktif.\nTezgâh hazır, marşa basılması bekleniyor Burak usta... 💻"
    @State private var isEngineRunning: Bool = false

    var body: some View {
        HStack(spacing: 0) {
            // SOL PANEL: KONTROL PANELİ VE ŞALTERLER
            VStack(alignment: .leading, spacing: 25) {
                VStack(alignment: .leading, spacing: 5) {
                    Text("DETER ENGINE")
                        .font(.system(.title, design: .monospaced))
                        .fontWeight(.black)
                        .foregroundColor(.white)
                    
                    Text("macOS Architecture Control")
                        .font(.caption)
                        .foregroundColor(.gray)
                }
                
                Divider().background(Color.gray.opacity(0.3))
                
                // M1/M2/M3/M4 İŞLEMCİLER İÇİN STAGE 2 ŞALTERİ
                Button(action: {
                    withAnimation {
                        isEngineRunning = true
                        terminalLog += "\n\n[SİSTEM]: Mac donanım katına sızılıyor..."
                        
                        // Köprü üzerinden ortak C++ ve ARM64 Assembly NEON motorunu ateşliyoruz!
                        if let reportFromCore = bridge.fireStage2AppleEngine() {
                            terminalLog = reportFromCore
                        }
                    }
                }) {
                    HStack {
                        Image(systemName: "gauge.badge.plus")
                        Text("STAGE 2: MAC MOTORUNU ATEŞLE")
                            .fontWeight(.bold)
                    }
                    .font(.body)
                    .foregroundColor(.white)
                    .padding()
                    .frame(maxWidth: .infinity)
                    .background(isEngineRunning ? Color.red : Color.orange)
                    .cornerRadius(8)
                }
                .buttonStyle(PlainButtonStyle()) // Mac'in standart gri buton temasını eziyoruz
                .disabled(isEngineRunning)
                
                Spacer()
                
                // DURUM LAMBASI
                HStack {
                    Circle()
                        .fill(isEngineRunning ? Color.green : Color.red)
                        .frame(width: 10, height: 10)
                    Text(isEngineRunning ? "MOTOR DURUMU: SAF PERFORMANS" : "MOTOR DURUMU: BEKLEMEDE")
                        .font(.system(size: 10, design: .monospaced))
                        .foregroundColor(.gray)
                }
            }
            .padding()
            .frame(width: 250)
            .background(Color(red: 0.12, green: 0.12, blue: 0.15))
            
            // SAĞ PANEL: GENİŞ SİMÜLASYON VE TERMİNAL EKRANI
            VStack(alignment: .leading, spacing: 10) {
                Text("DeterEngine Terminal Log")
                    .font(.system(size: 11, design: .monospaced))
                    .foregroundColor(.gray)
                    .padding(.horizontal)
                    .padding(.top, 10)
                
                ScrollView {
                    Text(terminalLog)
                        .font(.system(size: 13, design: .monospaced))
                        .foregroundColor(isEngineRunning ? .green : .white)
                        .padding()
                        .frame(maxWidth: .infinity, alignment: .leading)
                }
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .background(Color(red: 0.05, green: 0.05, blue: 0.07))
                .cornerRadius(6)
                .padding([.horizontal, .bottom])
            }
            .background(Color(red: 0.08, green: 0.08, blue: 0.1))
        }
        .frame(minWidth: 700, minHeight: 400) // Mac penceresinin minimum boyut sınırı
    }
}

// Mac için önizleme kilidi
struct MacContentView_Previews: PreviewProvider {
    static var previews: some View {
        MacContentView()
    }
}
