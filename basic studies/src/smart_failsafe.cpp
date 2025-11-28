#include <iostream>
#include <string>
#include <cmath> // Matematik icin (karekok vs.)

// --- ARDUPILOT BENZERI YAPI ---
// ArduPilot'ta konum verisi (Vector3f) boyle tutulur.
struct Location {
    float x; // Kuzey (Metre)
    float y; // Dogu (Metre)
    float z; // Yukseklik (Metre)
};

// --- AKILLI FAILSAFE SINIFI ---
class SmartBatteryFailsafe {
private:
    // Parametreler (Ayarlar)
    float _critical_voltage; // Kritik Voltaj (V)
    float _max_distance;     // RTL icin maksimum mesafe (m)
    
    // Durum Degiskenleri
    bool _failsafe_triggered;

public:
    // Constructor (Kurucu): Ayarlari yukle
    SmartBatteryFailsafe(float voltage_limit, float dist_limit) {
        _critical_voltage = voltage_limit;
        _max_distance = dist_limit;
        _failsafe_triggered = false;
    }

    // Ana Kontrol Fonksiyonu (Loop icinde cagirilir)
    // Girdi: Pil Voltaji, Anlik Konum, Kalkis Konumu
    // Cikti: Yapilmasi gereken eylem (String olarak)
    std::string update(float battery_voltage, const Location& current_loc, const Location& home_loc) {
        
        // 1. Eger zaten tetiklendiyse tekrar hesaplama
        if (_failsafe_triggered) {
            return "FAILSAFE_ACTIVE"; 
        }

        // 2. Voltaj Kontrolu
        if (battery_voltage > _critical_voltage) {
            return "NORMAL"; // Her sey yolunda
        }

        // --- KRITIK DURUM: PIL BITIYOR! ---
        std::cout << ">> UYARI: Kritik Voltaj Tespit Edildi! (" << battery_voltage << "V)" << std::endl;
        _failsafe_triggered = true;

        // 3. Mesafe Hesabi (Pisagor: a^2 + b^2 = c^2)
        float dist_x = current_loc.x - home_loc.x;
        float dist_y = current_loc.y - home_loc.y;
        float distance_to_home = std::sqrt(dist_x*dist_x + dist_y*dist_y);

        std::cout << ">> Eve Mesafe: " << distance_to_home << " metre." << std::endl;

        // 4. Karar Mekanizmasi (Decision Logic)
        if (distance_to_home > _max_distance) {
            // Cok uzaktayiz, inmek tehlikeli olabilir (deniz/orman ustunde olabiliriz).
            // Mecburen eve donmeye calis.
            return "DO_RTL"; 
        } else {
            // Eve yakiniz veya pil cok kritik. Risk alma, hemen in.
            return "DO_LAND";
        }
    }

    // Sistemi sifirlamak icin (Pil degisince)
    void reset() {
        _failsafe_triggered = false;
        std::cout << ">> Failsafe sifirlandi." << std::endl;
    }
};

// --- ANA PROGRAM (SIMULASYON) ---
int main() {
    // 1. Sistemi Baslat (10.5V kritik sinir, 500m mesafe siniri)
    SmartBatteryFailsafe myFailsafe(10.5f, 500.0f);

    // 2. Senaryo Verileri
    Location home = {0, 0, 0};       // Kalkis noktasi
    Location drone = {400, 300, 50}; // Drone konumu (3-4-5 ucgeni: 500m uzakta)
    
    float current_voltage = 11.0f; // Pil dolu

    // 3. Ucus Dongusu (Loop)
    for (int i = 0; i < 5; i++) {
        std::cout << "\n--- Dongu " << i << " ---" << std::endl;
        
        // Voltaj dusuyor...
        current_voltage -= 0.2f; 
        
        // Failsafe kontrolu yap (Referans ile veri gonderiyoruz!)
        std::string action = myFailsafe.update(current_voltage, drone, home);
        
        std::cout << "Aksiyon: " << action << std::endl;

        if (action == "DO_RTL" || action == "DO_LAND") {
            std::cout << "!!! MÜDAHALE EDİLDİ !!!" << std::endl;
            break; // Donguyu kir
        }
    }

    return 0;
}