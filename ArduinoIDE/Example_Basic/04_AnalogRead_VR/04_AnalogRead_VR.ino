// ============================================================
//  SKU-1015 ESP32 Breakout Board — 04 Analog Read (VR)
//  อ่านค่า VR (Potentiometer) บนบอร์ด = GPIO34
//  ADC 12-bit: ค่า 0-4095 เทียบแรงดัน 0-3.3V
// ============================================================

#define VR_PIN 34   // VR บนบอร์ด (Input-only)

void setup() {
  Serial.begin(115200);
  pinMode(VR_PIN, INPUT);
  Serial.println("Turn the VR knob!");
}

void loop() {
  int raw = analogRead(VR_PIN);            // อ่านค่า 0-4095
  float volt = raw * 3.3 / 4095.0;         // แปลงเป็นโวลต์
  int percent = map(raw, 0, 4095, 0, 100); // แปลงเป็นเปอร์เซ็นต์

  Serial.printf("VR Raw: %4d | Voltage: %.2f V | %3d %%\n",
                raw, volt, percent);
  delay(200);
}
