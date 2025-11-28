#include <iostream> // Ekrana yazmak icin (Python'daki import sys gibi)

// --- FONKSIYON TANIMI ---
// Girdi: PWM sinyali (Tam sayi - int)
// Cikti: Itki Kuvveti (Virgullu sayi - float)
float calculate_thrust(int pwm_input) {
    // 1. PWM Sinirlandirma (Safety)
    if (pwm_input < 1000) pwm_input = 1000;
    if (pwm_input > 2000) pwm_input = 2000;

    // 2. Lineer Donusum (1000-2000 arasi -> 0-10 Newton)
    // Formül: (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    float thrust = (pwm_input - 1000) * (10.0f / 1000.0f);
    
    return thrust;
}

// --- ANA PROGRAM (MAIN) ---
// C++ her zaman burdan baslar.
int main() {
    int throttle_pwm = 1500; // %50 Gaz
    
    // Fonksiyonu cagir
    float current_thrust = calculate_thrust(throttle_pwm);

    // Ekrana bas (std::cout = Console Out)
    std::cout << "PWM Girisi: " << throttle_pwm << std::endl;
    std::cout << "Uretilen Itki: " << current_thrust << " Newton" << std::endl;

    return 0; // "Hatasiz bitti" kodu
}