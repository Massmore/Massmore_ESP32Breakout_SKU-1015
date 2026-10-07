# Example_Advance — ตัวอย่างขั้นสูง SKU-1015

ตัวอย่างที่ใช้จอแสดงผลและอุปกรณ์หลายอย่างพร้อมกัน ควรผ่านตัวอย่างใน `Example_Basic` มาก่อน

| ตัวอย่าง | รายละเอียด | Library ที่ต้องใช้ |
|---|---|---|
| `LCD_AnalogInput` | แสดงค่า Analog 5 ช่องบนจอ TFT ST7789 | TFT_eSPI* |
| `OLED_I2C` | เดโมจอ OLED SSD1306 128×64 เต็มรูปแบบ (I2C 0x3C) | Adafruit_SSD1306 + Adafruit_GFX + Adafruit_BusIO |
| `ServoMotor` | VR ควบคุม Servo 2 ตัว + สวิตช์ Toggle LED | ESP32Servo |
| `DCMotor` | ควบคุมความเร็ว/ทิศทางมอเตอร์ 2 ช่องด้วย PWM | - |
| `SKU_1015_ESP32_FACTORY_TEST` | โปรแกรมทดสอบโรงงาน — จอ TFT 3 หน้า ทดสอบ Analog/VR/Servo/Motor กดปุ่ม SW เปลี่ยนหน้า | TFT_eSPI* + ESP32Servo |

> ต้องการแฟลชโปรแกรม Factory Test โดยไม่ต้อง compile → ใช้ไฟล์ .bin ใน [`firmware/`](../../firmware)

\* ใช้ TFT_eSPI จากโฟลเดอร์ `ArduinoIDE/libraries/TFT_eSPI` ของโปรเจกต์นี้ ซึ่ง**ตั้งค่า `User_Setup.h` สำหรับบอร์ดนี้แล้ว** (ST7789 240×240, CLK=18, MOSI=23, RES=4, DC=2, CS=-1, BGR, Inversion ON)

**หมายเหตุ:** โค้ด PWM ใช้ API ของ ESP32 core 2.x (`ledcSetup`/`ledcAttachPin`) — แนะนำติดตั้ง esp32 core **v2.0.17**
