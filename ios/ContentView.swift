import SwiftUI

struct ContentView: View {
    // Bizim Objective-C++ köprüsünü içeri çağırıyoruz usta
    let bridge = DeterEngineBridge()
    
    // Ekranda görünecek canlı rapor metni
    @State private var dashboardReport: String = "DeterEngine Apple Sistemine Hoş Geldiniz.\nMarş basılmaya hazır usta! ⚙️"
    @State private var isEngineFiring: Bool = false

    var body: some View {
        ZStack {
            // Sanayi işi koyu tema arka plan
            Color(red: 0.1, green: 0.1, blue: 0.12)
                .edgesIgnoringSafeArea(.all)
            
            VStack(spacing: 30) {
                // BAŞLIK GRUBU
                VStack(spacing: 8) {
                    Text("DETER ENGINE")
                        .font(.system(.largeTitle, design: .monospaced))
                        .fontWeight(.black)
                        .foregroundColor(.white)
                    
                    Text("Apple Silicon Performance Unit")
                        .font(.caption)
                        .foregroundColor(.gray)
                }
                .padding(.top, 40)
                
                // CANLI LOG / DASHBOARD EKRANI
                ScrollView {
                    Text(dashboardReport)
                        .font(.system(.body, design: .monospaced))
                        .foregroundColor(isEngineFiring ? .green : .white)
                        .padding()
                        .frame(maxWidth: .infinity, alignment: .leading)
                }
                .frame(height: 250)
                .background(Color(red: 0.05, green: 0.05, blue: 0.07))
                .cornerRadius(12)
                .overlay(
                    RoundedRectangle(cornerRadius: 12)
                        .stroke(isEngineFiring ? Color.green : Color.gray.opacity(0.3), lineWidth: 2)
                )
                .padding(.horizontal)
                
                // BOMBA BUTON: STAGE 2 ŞALTERİ
                Button(action: {
                    withAnimation {
                        isEngineFiring = true
                        // İŞTE BAĞLANTI: Köprü üzerinden C++ ve Assembly canavarlarını tetikliyoruz!
                        if let reportFromCore = bridge.fireStage2AppleEngine() {
                            dashboardReport = reportFromCore
                        }
                    }
                }) {
                    HStack {
                        Image(systemName: "flame.fill")
                        Text("STAGE 2: MARŞA BAS")
                            .fontWeight(.bold)
                    }
                    .font(.headline)
                    .foregroundColor(.white)
                    .padding()
                    .frame(maxWidth: .infinity)
                    .background(isEngineFiring ? Color.red : Color.blue)
                    .cornerRadius(10)
                    .shadow(color: isEngineFiring ? .red.opacity(0.5) : .blue.opacity(0.3), radius: 10)
                }
                .padding(.horizontal)
                .disabled(isEngineFiring) // Bir kere basılınca kilitlensin
                
                Spacer()
            }
        }
    }
}

// Xcode önizlemesi için emniyet kilidi
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}

