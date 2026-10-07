// ============================================================
//  SKU-1015 ESP32 Breakout Board — 03 Button / Switch
//  อ่านค่าสวิตช์บนบอร์ด (SW = GPIO36)
//  ⚠️ GPIO36 เป็นขา Input-only และไม่มี Internal Pull-up
//     (บอร์ดมี Hardware Pull-up ให้แล้ว กดปุ่ม = LOW)
// ============================================================

#define SW_PIN 36   // สวิตช์บนบอร์ด (Active LOW)

bool lastState = HIGH;
int pressCount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT);   // ห้ามใช้ INPUT_PULLUP กับ GPIO36
  Serial.println("Press the SW button!");
}

void loop() {
  bool state = digitalRead(SW_PIN);

  // ตรวจจับขอบขาลง (ปุ่มเพิ่งถูกกด) พร้อมกัน Debounce
  if (state == LOW && lastState == HIGH) {
    pressCount++;
    Serial.printf("Button Pressed! Count = %d\n", pressCount);
    delay(50);  // Debounce
  }
  lastState = state;
  delay(10);
}
