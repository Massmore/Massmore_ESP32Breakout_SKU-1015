# PlatformIO — ตัวอย่าง SKU-1015 สำหรับ VS Code

โปรเจกต์ PlatformIO เดียว รวมตัวอย่างทั้งหมด 15 ตัว (ตัวอย่างพื้นฐาน 10 + ขั้นสูง 5) โค้ดเดียวกับโฟลเดอร์ [`ArduinoIDE`](../ArduinoIDE)
**Build ผ่านครบทุกตัวแล้ว** — ใช้ library ชุดเดียวกับ Arduino IDE จาก `../ArduinoIDE/libraries` (TFT_eSPI ตั้งค่าจอ ST7789 ไว้แล้ว ไม่ต้องดาวน์โหลด library เพิ่ม)

| รายการ | ค่า |
|---|---|
| Board | ESP32-WROOM-32E 38PIN CH340 (Massmore SKU-1016-1) → `esp32dev` |
| Platform | `espressif32 @ 6.9.0` (Arduino-ESP32 core 2.0.17) |
| Serial Monitor | 115200 |

## วิธีใช้

1. ติดตั้ง [VS Code](https://code.visualstudio.com/) + extension **PlatformIO IDE** และ [Driver CH340](https://www.wch-ic.com/downloads/CH341SER_EXE.html)
2. ดาวน์โหลด repo ทั้งหมด (**Code → Download ZIP**) แล้วแตกไฟล์ — *ห้ามแยกโฟลเดอร์ PlatformIO ออกมาเดี่ยวๆ เพราะต้องใช้ library ใน `../ArduinoIDE/libraries`*
3. VS Code → **File → Open Folder…** → เลือกโฟลเดอร์ `PlatformIO` นี้ (ครั้งแรกจะดาวน์โหลด platform อัตโนมัติ รอสักครู่)
4. เลือกตัวอย่างจากปุ่ม **env** ที่แถบสถานะด้านล่าง (หรือแก้ `default_envs` ใน `platformio.ini`)
5. กด **Upload** (→) แล้วเปิด **Serial Monitor**

ใช้ CLI ก็ได้:

```bash
pio run -e 07_servo_sweep -t upload
pio device monitor
```

## รายการ env

| env | โฟลเดอร์ใน `src/` | รายละเอียด |
|---|---|---|
| `01_hello_serial` | `01_HelloWorld_Serial` | Serial + ข้อมูลชิป |
| `02_blink_led` | `02_Blink_LED` | กะพริบ LED (GPIO2) |
| `03_button_switch` | `03_Button_Switch` | อ่านสวิตช์ SW (GPIO36) |
| `04_analog_vr` | `04_AnalogRead_VR` | อ่านค่า VR (GPIO34) |
| `05_analog_all` | `05_AnalogRead_All` | อ่าน Analog IO1–IO7 |
| `06_pwm_fade` | `06_PWM_Fade` | PWM หรี่ไฟ (LEDC) |
| `07_servo_sweep` | `07_Servo_Sweep` | Servo 3 ช่อง |
| `08_dcmotor_basic` | `08_DCMotor_Basic` | มอเตอร์ DC 2 ช่อง |
| `09_i2c_scanner` | `09_I2C_Scanner` | สแกนอุปกรณ์ I2C |
| `10_wifi_scan` | `10_WiFi_Scan` | WiFi Scan + Connect |
| `adv_dcmotor` | `DCMotor` | มอเตอร์ DC ปรับความเร็วด้วย PWM |
| `adv_lcd_analog` | `LCD_AnalogInput` | ค่า Analog บนจอ TFT ST7789 |
| `adv_oled_i2c` | `OLED_I2C` | จอ OLED SSD1306 128×64 |
| `adv_servo_vr` | `ServoMotor` | VR ควบคุม Servo + Switch |
| `factory_test` | `SKU_1015_ESP32_FACTORY_TEST` | โปรแกรมทดสอบโรงงาน (ไฟล์ .bin สำเร็จรูปอยู่ที่ [`../firmware`](../firmware)) |

## เขียนโปรแกรมของตัวเอง

สร้างโฟลเดอร์ใหม่ใน `src/` เช่น `src/MyProject/main.cpp` แล้วเพิ่มใน `platformio.ini`:

```ini
[env:my_project]
build_src_filter = +<MyProject/>
```

> ต่างจาก Arduino IDE: ต้องมี `#include <Arduino.h>` และประกาศ prototype ของฟังก์ชันก่อนเรียกใช้ (ดูตัวอย่างใน `src/`)

## แก้ปัญหา

- **อัปโหลดไม่เข้า** — กด BOOT ค้าง → กด EN → ปล่อย EN → ปล่อย BOOT แล้วกด Upload ใหม่ / ลด `upload_speed` เป็น 460800
- **ไม่เจอพอร์ต** — ตรวจ Driver CH340 และใช้สาย USB ที่ส่งข้อมูลได้
- **Servo / Motor ไม่หมุน** — ต้องต่อไฟ DC IN 6–12V เข้าบอร์ด SKU-1015
