#include <iostream>

// --- ENUM TANIMI (Sözlük) ---
// Kodun içinde 0, 1, 2 yazmak yerine isim kullaniyoruz.
// ArduPilot'un modu.h dosyasinda da aynen boyle yazar.
enum FlightMode {
    STABILIZE = 0, // Manuel Denge
    ALT_HOLD  = 1, // Yukseklik Sabitleme
    LOITER    = 2, // GPS Konum Sabitleme
    RTL       = 3, // Eve Donus (Return to Launch)
    LAND      = 9  // Inis (ArduPilot standardi 9'dur)
};

// --- MOD KONTROL FONKSIYONU ---
void check_flight_mode(int mode_input) {
    
    // Gelen sayiyi FlightMode tipine zorla (Casting)
    // Bu, derleyiciye "Ben ne yaptigimi biliyorum" demektir.
    FlightMode current_mode = static_cast<FlightMode>(mode_input);

    // Switch: "Anahtari cevir"
    switch (current_mode) {
        
        case STABILIZE:
            std::cout << ">> MOD: STABILIZE" << std::endl;
            std::cout << "   - Pilot tam kontrolde." << std::endl;
            std::cout << "   - GPS: Gerekmez." << std::endl;
            break; // Buradan cik, asagiya dusme!

        case ALT_HOLD:
            std::cout << ">> MOD: ALTITUDE HOLD" << std::endl;
            std::cout << "   - Barometre aktif." << std::endl;
            break;

        case LOITER:
            std::cout << ">> MOD: LOITER" << std::endl;
            std::cout << "   - GPS Kilitlenmesi bekleniyor..." << std::endl;
            std::cout << "   - Pozisyon hatasi hesaplaniyor." << std::endl;
            break;

        case RTL:
            std::cout << ">> UYARI: EVE DONUS BASLATILDI!" << std::endl;
            std::cout << "   - Hedef: Kalkis noktasi (Home)." << std::endl;
            break;

        // Hicbiri degilse bu calisir (Guvenlik agi)
        default:
            std::cout << ">> HATA: Gecersiz Ucus Modu! (" << mode_input << ")" << std::endl;
            std::cout << "   - Failsafe tetiklendi: Inis yapiliyor..." << std::endl;
            break;
    }
}

// --- ANA PROGRAM ---
int main() {
    int user_input;

    std::cout << "--- ARDUPILOT MODE SWITCHER ---" << std::endl;
    std::cout << "0: Stabilize | 1: AltHold | 2: Loiter | 3: RTL" << std::endl;
    std::cout << "Mod seciniz: ";
    
    // Kullanicidan veri al (Console Input)
    std::cin >> user_input;

    // Fonksiyona gonder
    check_flight_mode(user_input);

    return 0;
}