// ============================================================
//  SKU-1015 ESP32 Breakout Board — 09 I2C Scanner
//  สแกนหาอุปกรณ์บนบัส I2C (SDA=GPIO21, SCL=GPIO22)
//  ใช้ตรวจสอบ OLED SSD1306 (0x3C) และเซนเซอร์ I2C อื่นๆ
//  พอร์ต I2C บนบอร์ด: PH2.0 4P
// ============================================================

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);   // SDA=21, SCL=22 (ค่า default ของ ESP32)
  Serial.println("=== SKU-1015 I2C Scanner ===");
}

void loop() {
  byte count = 0;
  Serial.println("Scanning...");
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("  Found device at 0x%02X\n", addr);
      count++;
    }
  }
  if (count == 0) Serial.println("  No I2C devices found!");
  else            Serial.printf("  Total: %d device(s)\n", count);
  Serial.println();
  delay(3000);
}
