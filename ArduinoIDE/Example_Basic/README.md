# Example_Basic — ตัวอย่างพื้นฐาน SKU-1015

ตัวอย่างเรียงลำดับจากง่ายไปยาก แนะนำให้ทำตามลำดับ 01 → 10
ทุกตัวอย่างใช้ Serial Monitor ที่ **115200 baud** และใช้ขาตรงกับบอร์ด SKU-1015

| # | ตัวอย่าง | ขาที่ใช้ | Library เพิ่มเติม |
|---|---|---|---|
| 01 | HelloWorld_Serial | - | - |
| 02 | Blink_LED | GPIO2 (LED โมดูล)* | - |
| 03 | Button_Switch | GPIO36 (SW) | - |
| 04 | AnalogRead_VR | GPIO34 (VR) | - |
| 05 | AnalogRead_All | IO1–IO7 | - |
| 06 | PWM_Fade | GPIO5 (IO6) | - |
| 07 | Servo_Sweep | GPIO19, 32, 33 | ESP32Servo |
| 08 | DCMotor_Basic | GPIO27, 26, 16, 17 | - |
| 09 | I2C_Scanner | GPIO21, 22 | Wire (มากับ core) |
| 10 | WiFi_Scan | - | WiFi (มากับ core) |

\* GPIO2 ใช้ร่วมกับ LCD_DC — หากต่อจอ TFT อยู่ให้เปลี่ยนขาตามคอมเมนต์ในโค้ด

**ข้อควรรู้:**
- GPIO34, 35, 36 เป็นขา **Input-only** และไม่มี Internal Pull-up
- ตัวอย่าง 07 (Servo) และ 08 (Motor) ต้องต่อไฟ **DC IN 6–12V** เข้าบอร์ดก่อน
- โค้ด PWM ใช้ API ของ ESP32 core **2.x** (`ledcSetup`/`ledcAttachPin`) — หากใช้ core 3.x ให้เปลี่ยนเป็น `ledcAttach(pin, freq, res)` และ `ledcWrite(pin, duty)`
