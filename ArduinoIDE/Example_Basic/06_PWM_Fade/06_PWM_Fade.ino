// ============================================================
//  SKU-1015 ESP32 Breakout Board — 06 PWM Fade (LEDC)
//  สร้างสัญญาณ PWM หรี่ไฟ LED ที่ขา IO6 (GPIO5)
//  ESP32 core 2.x: ledcSetup() + ledcAttachPin()
//  (core 3.x ใช้ ledcAttach(pin, freq, res) แทน)
// ============================================================

#define PWM_PIN   5     // IO6 บนบอร์ด
#define PWM_CH    0     // Channel 0-15
#define PWM_FREQ  5000  // 5 kHz
#define PWM_RES   8     // 8-bit (0-255)

void setup() {
  Serial.begin(115200);
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_PIN, PWM_CH);
  Serial.println("PWM Fade Start!");
}

void loop() {
  // สว่างขึ้น 0 -> 255
  for (int duty = 0; duty <= 255; duty += 5) {
    ledcWrite(PWM_CH, duty);
    delay(20);
  }
  // หรี่ลง 255 -> 0
  for (int duty = 255; duty >= 0; duty -= 5) {
    ledcWrite(PWM_CH, duty);
    delay(20);
  }
}
