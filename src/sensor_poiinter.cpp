#include <iostream>

// --- 1. VERI PAKETI (STRUCT) ---
// ArduPilot'ta "Vector3f" boyle bir seydir.
// IMU verilerini tutan sanal bir kutu tanimliyoruz.
struct IMU_Data {
    float acc_x;
    float acc_y;
    float acc_z;
    float temp; // Sicaklik
};

// --- 2. SENSOR OKUMA FONKSIYONU ---
// DIKKAT: Girdi olarak 'IMU_Data' degil, 'IMU_Data*' (Yildizli) aliyor!
// Yani: "Bana veriyi getirme, verinin ADRESINI getir."
void read_fake_sensor(IMU_Data* sensor_ptr) {
    
    // Adrese gidip (->) degerleri yaziyoruz.
    // Eger pointer olmasaydi '.' kullanirdik (sensor.acc_x gibi).
    // Pointer oldugu icin '->' (Ok isareti) kullaniyoruz.
    
    // Simule edilmis veriler (Sanki I2C'den okuduk)
    sensor_ptr->acc_x = 0.05f;
    sensor_ptr->acc_y = -0.02f;
    sensor_ptr->acc_z = 9.81f; // Yercekimi
    sensor_ptr->temp  = 45.5f; // Isinmis biraz :)
    
    std::cout << "[Driver] Veriler adrese (" << sensor_ptr << ") yazildi." << std::endl;
}

// --- 3. ANA PROGRAM ---
int main() {
    // RAM'de bos bir kutu olusturuyoruz.
    IMU_Data my_imu = {0, 0, 0, 0}; 

    std::cout << "--- ONCE ---" << std::endl;
    std::cout << "Acc Z: " << my_imu.acc_z << std::endl; // 0 cikmali

    // KRITIK AN: Fonksiyona kutuyu degil, ADRESINI (&) gonderiyoruz.
    // &my_imu = "my_imu degiskeninin RAM'deki adresi"
    read_fake_sensor(&my_imu);

    std::cout << "--- SONRA ---" << std::endl;
    std::cout << "Acc Z: " << my_imu.acc_z << std::endl; // 9.81 cikmali
    std::cout << "Sicaklik: " << my_imu.temp << " C" << std::endl;

    return 0;
}