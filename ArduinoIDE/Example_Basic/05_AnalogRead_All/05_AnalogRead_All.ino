// ============================================================
//  SKU-1015 ESP32 Breakout Board — 05 Analog Read All (IO1-IO7)
//  อ่านค่า Analog Input ทั้ง 7 ช่องบนบอร์ด
//  IO1=GPIO25, IO2=GPIO13, IO3=GPIO12, IO4=GPIO14,
//  IO5=GPIO15, IO6=GPIO5,  IO7=GPIO35 (Input-only)
//  ⚠️ IO6 (GPIO5) เป็น ADC ไม่ได้ — อ่านเป็น Digital แทน
// ============================================================

const int analogPins[7] = {25, 13, 12, 14, 15, 5, 35};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 7; i++) {
    pinMode(analogPins[i], INPUT);
  }
  Serial.println("=== SKU-1015 Analog Monitor ===");
}

void loop() {
  Serial.println("--- Read All Channels ---");
  for (int i = 0; i < 7; i++) {
    int pin = analogPins[i];
    if (pin == 5) {
      // GPIO5 ไม่มี ADC — อ่านค่าเป็น Digital 0/1
      Serial.printf("IO%d (GPIO%2d): D=%d\n", i + 1, pin, digitalRead(pin));
    } else {
      int raw = analogRead(pin);
      float volt = raw * 3.3 / 4095.0;
      Serial.printf("IO%d (GPIO%2d): %4d = %.2f V\n", i + 1, pin, raw, volt);
    }
  }
  Serial.println();
  delay(500);
}
