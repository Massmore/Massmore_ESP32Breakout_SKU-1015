// ============================================================
//  SKU-1015 ESP32 Breakout Board — 02 Blink LED
//  กะพริบ LED บนโมดูล ESP32 (GPIO2)
//  ⚠️ หมายเหตุ: GPIO2 ใช้ร่วมกับ LCD_DC ของจอ ST7789
//     หากต่อจอ TFT อยู่ ให้เปลี่ยนไปใช้ขา IO อื่น เช่น IO6 (GPIO5)
// ============================================================

#define LED_PIN 2   // LED บนโมดูล ESP32 (หรือเปลี่ยนเป็น 5 = IO6 เมื่อใช้จอ TFT)

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Blink LED Start!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // เปิด LED
  Serial.println("LED ON");
  delay(500);

  digitalWrite(LED_PIN, LOW);    // ปิด LED
  Serial.println("LED OFF");
  delay(500);
}
