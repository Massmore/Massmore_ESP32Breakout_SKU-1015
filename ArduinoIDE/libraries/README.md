# libraries — ไลบรารีที่ตั้งค่าสำหรับ SKU-1015 แล้ว

คัดลอกทุกโฟลเดอร์ในนี้ไปวางที่ `Documents/Arduino/libraries/` แล้วรีสตาร์ท Arduino IDE

| Library | ใช้กับ | หมายเหตุ |
|---|---|---|
| `TFT_eSPI` | จอ TFT IPS 240×240 ST7789 | ⭐ แก้ `User_Setup.h` ให้ตรงบอร์ดนี้แล้ว (CLK=18, MOSI=23, RES=4, DC=2, CS=-1) — **ถ้าติดตั้งจาก Library Manager ต้องตั้งค่าเองใหม่** |
| `Adafruit_SSD1306` | จอ OLED 128×64 (I2C 0x3C) | ใช้คู่กับ Adafruit_GFX |
| `Adafruit_GFX_Library` | กราฟิกพื้นฐานของจอ Adafruit | Dependency ของ SSD1306 |
| `Adafruit_BusIO` | I2C/SPI helper ของ Adafruit | Dependency ของ Adafruit_GFX (v1.16.1) |
| `ESP32Servo` | Servo 3 ช่อง (GPIO19, 32, 33) | ใช้แทน Servo.h ของ Arduino เดิม |

ไฟล์ `User_Setup.h` (สำรอง) ที่ root ของโฟลเดอร์นี้ คือค่าตั้งจอสำหรับบอร์ดนี้ — ใช้ทับไฟล์เดิมใน `TFT_eSPI/` เมื่ออัปเดตไลบรารีใหม่

หรือไม่ต้องคัดลอก: ตั้ง Arduino IDE → **File → Preferences → Sketchbook location** เป็นโฟลเดอร์ `ArduinoIDE` แล้วรีสตาร์ท

PlatformIO ใช้ library ชุดนี้โดยตรงผ่าน `lib_extra_dirs = ../ArduinoIDE/libraries`
