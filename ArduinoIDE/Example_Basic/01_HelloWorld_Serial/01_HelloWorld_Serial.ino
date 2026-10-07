// ============================================================
//  SKU-1015 ESP32 Breakout Board — 01 Hello World (Serial)
//  โปรแกรมแรก: ทดสอบการสื่อสาร Serial และข้อมูลชิป
//  บอร์ด: ESP32-WROOM-32E 38PIN + Breakout Board by Massmore
//  Serial Monitor: 115200 baud
// ============================================================

int counter = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);  // รอให้ Serial พร้อม

  Serial.println("========================================");
  Serial.println("  SKU-1015 ESP32 Breakout Board");
  Serial.println("  Hello World! - Board is Ready!");
  Serial.println("  by Massmore");
  Serial.println("========================================");
  Serial.printf("  Chip Model : %s\n", ESP.getChipModel());
  Serial.printf("  CPU Freq   : %d MHz\n", getCpuFrequencyMhz());
  Serial.printf("  Flash Size : %d bytes\n", ESP.getFlashChipSize());
  Serial.printf("  Free Heap  : %d bytes\n", ESP.getFreeHeap());
  Serial.println("========================================");
}

void loop() {
  counter++;
  Serial.printf("[%4d] Uptime: %lu s\n", counter, millis() / 1000);
  delay(1000);
}
