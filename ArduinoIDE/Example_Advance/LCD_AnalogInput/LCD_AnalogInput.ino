#include <TFT_eSPI.h>  // ใช้ไลบรารี TFT_eSPI (ตั้งค่าใน User_Setup.h ก่อนใช้งาน)

TFT_eSPI tft = TFT_eSPI();  // สร้างอ็อบเจ็กต์สำหรับควบคุมจอ

// กำหนดขา Analog Input
const int analogPins[5] = {25, 13, 12, 14, 15};
int analogValues[5];  // ตัวแปรเก็บค่าที่อ่านได้

void setup() {
  Serial.begin(115200);

  // เริ่มต้นจอแสดงผล
  tft.init();
  tft.setRotation(0);  // หมุนหน้าจอได้ 0-3 แล้วแต่การติดตั้ง
  tft.fillScreen(TFT_BLACK);  // เคลียร์หน้าจอด้วยสีดำ
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);  // ตัวอักษรสีเขียว พื้นหลังดำ

  // แสดงข้อความเริ่มต้น
  tft.setCursor(20, 10);
  tft.println("Analog Monitor");
  delay(1000);
}

void loop() {
  // อ่านค่า Analog ทุกช่อง
  for (int i = 0; i < 5; i++) {
    analogValues[i] = analogRead(analogPins[i]);
  }

  // เคลียร์พื้นหลังบางส่วนก่อนเขียนค่าใหม่
  tft.fillRect(0, 40, 240, 200, TFT_BLACK);

  // แสดงผลค่า Analog
  for (int i = 0; i < 5; i++) {
    tft.setCursor(10, 50 + i * 30);
    tft.printf("AIN%d (GPIO%d): %4d", i + 1, analogPins[i], analogValues[i]);
  }

  delay(500);  // หน่วงเวลา 0.5 วินาที
}
