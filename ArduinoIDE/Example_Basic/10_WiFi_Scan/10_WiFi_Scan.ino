// ============================================================
//  SKU-1015 ESP32 Breakout Board — 10 WiFi Scan & Connect
//  สแกนเครือข่าย WiFi 2.4GHz แล้วเชื่อมต่อ Router
//  ⚠️ ESP32 รองรับเฉพาะ WiFi 2.4 GHz (ไม่รองรับ 5 GHz)
// ============================================================

#include <WiFi.h>

const char* SSID = "YOUR_WIFI_NAME";       // << แก้เป็นชื่อ WiFi ของคุณ
const char* PASS = "YOUR_WIFI_PASSWORD";   // << แก้เป็นรหัสผ่าน

void setup() {
  Serial.begin(115200);
  delay(1000);

  // 1) สแกนเครือข่ายรอบตัว
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  int n = WiFi.scanNetworks();
  Serial.printf("Found %d networks:\n", n);
  for (int i = 0; i < n; i++) {
    Serial.printf("  %2d) %-24s  %4d dBm\n",
                  i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }

  // 2) เชื่อมต่อ WiFi
  Serial.printf("\nConnecting to %s ...\n", SSID);
  WiFi.begin(SSID, PASS);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 30) {
    delay(500);
    Serial.print(".");
    retry++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nConnected! IP = %s\n", WiFi.localIP().toString().c_str());
  } else {
    Serial.println("\nConnect failed. Check SSID/Password.");
  }
}

void loop() {}
