// ============================================================
//  SKU-1015 ESP32 Breakout Board — 07 Servo Sweep
//  กวาด Servo 3 ช่องบนบอร์ด: Servo1=GPIO19, Servo2=GPIO32, Servo3=GPIO33
//  Library: ESP32Servo (ติดตั้งจาก Library Manager)
//  ⚠️ ไฟเลี้ยง Servo มาจาก DC-DC 5V/3A บนบอร์ด — ต้องต่อไฟ DC IN 6-12V
// ============================================================

#include <ESP32Servo.h>

#define SERVO1_PIN 19
#define SERVO2_PIN 32
#define SERVO3_PIN 33

Servo servo1, servo2, servo3;

void setup() {
  Serial.begin(115200);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  Serial.println("Servo Sweep Start!");
}

void loop() {
  // กวาด 0 -> 180 องศา
  for (int angle = 0; angle <= 180; angle += 2) {
    servo1.write(angle);
    servo2.write(angle);
    servo3.write(180 - angle);  // Servo3 หมุนสวนทาง
    delay(15);
  }
  delay(500);

  // กวาดกลับ 180 -> 0 องศา
  for (int angle = 180; angle >= 0; angle -= 2) {
    servo1.write(angle);
    servo2.write(angle);
    servo3.write(180 - angle);
    delay(15);
  }
  delay(500);
}
