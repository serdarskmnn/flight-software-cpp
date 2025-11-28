#include <iostream>
#include <string>

// --- CLASS TANIMI (Mavi Kopyasi) ---
class SimpleDrone {
private:
    // Bu degiskenlere sadece bu sinifin icindeki fonksiyonlar dokunabilir.
    // Disaridan "drone.battery_voltage = 0;" dersen HATA verir. Guvenlik budur.
    float _battery_voltage;
    bool _is_armed;
    std::string _name;

public:
    // Constructor (Kurucu): Drone ilk yaratildiginda calisan fonksiyon
    SimpleDrone(std::string name, float initial_voltage) {
        _name = name;
        _battery_voltage = initial_voltage;
        _is_armed = false; // Guvenlik icin baslangicta hep kapali
        std::cout << "[" << _name << "] Sistem baslatildi. Voltaj: " << _battery_voltage << "V" << std::endl;
    }

    // Eylem: Motorlari Aktif Et
    void arm_motors() {
        if (_battery_voltage < 10.0f) {
            std::cout << "[" << _name << "] HATA: Dusuk pil! Arm yapilamaz." << std::endl;
            return;
        }
        
        _is_armed = true;
        std::cout << "[" << _name << "] *** ARMED *** Motorlar donuyor!" << std::endl;
    }

    // Eylem: Motorlari Kapat
    void disarm_motors() {
        _is_armed = false;
        std::cout << "[" << _name << "] DISARMED. Guvenli." << std::endl;
    }

    // Eylem: Pil Guncelle (Sensor verisi gibi)
    void update_battery(float new_voltage) {
        _battery_voltage = new_voltage;
        
        // Otomatik koruma mantigi
        if (_is_armed && _battery_voltage < 9.5f) {
            std::cout << "[" << _name << "] ACIL DURUM: Pil kritik! Motorlar kapatiliyor..." << std::endl;
            disarm_motors(); // Kendi fonksiyonunu cagirabilir
        }
    }
    
    // Getter: Sadece okumaya izin ver (Degistirmeye degil)
    float get_voltage() {
        return _battery_voltage;
    }
};

// --- ANA PROGRAM ---
int main() {
    // 1. Iki farkli drone uretiyoruz (Nesne/Object)
    SimpleDrone drone1("Alpha", 12.6f); // 3S Lipo dolu
    SimpleDrone drone2("Beta", 9.0f);   // 3S Lipo bitik

    std::cout << "\n--- TEST 1: Normal Kalkis ---" << std::endl;
    drone1.arm_motors(); // Basarili olmali

    std::cout << "\n--- TEST 2: Dusuk Pille Kalkis ---" << std::endl;
    drone2.arm_motors(); // Hata vermeli

    std::cout << "\n--- TEST 3: Havada Pil Bitmesi ---" << std::endl;
    // Drone1 havada (Armed), pili aniden dusuruyoruz
    drone1.update_battery(9.4f); 

    return 0;
}