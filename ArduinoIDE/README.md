# ArduinoIDE — ตัวอย่าง SKU-1015 สำหรับ Arduino IDE

| โฟลเดอร์ | รายละเอียด |
|---|---|
| [`Example_Basic/`](Example_Basic) | ตัวอย่างพื้นฐาน 10 บท (เริ่มที่นี่) |
| [`Example_Advance/`](Example_Advance) | ตัวอย่างขั้นสูง + โปรแกรม Factory Test |
| [`libraries/`](libraries) | ไลบรารีที่ตั้งค่าสำหรับบอร์ดนี้แล้ว (TFT_eSPI, Adafruit GFX/SSD1306/BusIO, ESP32Servo) |

## ติดตั้ง

1. ติดตั้ง [Arduino IDE 2](https://www.arduino.cc/en/software) + [Driver CH340](https://www.wch-ic.com/downloads/CH341SER_EXE.html)
2. **File → Preferences → Additional boards manager URLs** ใส่
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. **Boards Manager** → ค้นหา `esp32` → ติดตั้ง **esp32 by Espressif Systems v2.0.17** (โค้ด PWM ใช้ API ของ core 2.x)
4. **Tools → Board → ESP32 Dev Module** · Upload Speed `921600` · เลือก Port ของบอร์ด
5. ติดตั้ง library — เลือก **วิธีใดวิธีหนึ่ง**
   - **A. คัดลอก** ทุกโฟลเดอร์ใน `libraries/` ไปไว้ที่ `Documents/Arduino/libraries/` แล้วรีสตาร์ท Arduino IDE
   - **B. ไม่ต้องคัดลอก** — ตั้ง **File → Preferences → Sketchbook location** เป็นโฟลเดอร์ `ArduinoIDE` นี้ แล้วรีสตาร์ท (Arduino IDE จะใช้ `ArduinoIDE/libraries` ทันที)
6. เปิด `Example_Basic/01_HelloWorld_Serial/01_HelloWorld_Serial.ino` → Upload → Serial Monitor `115200`

> ⚠️ ถ้ามี TFT_eSPI รุ่นอื่นติดตั้งอยู่แล้ว ให้ลบออกหรือใช้ไฟล์ `libraries/User_Setup.h` ทับ — ไม่เช่นนั้นจอจะไม่แสดงผล
