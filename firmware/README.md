# SKU-1015 — Factory Test Firmware

เฟิร์มแวร์ทดสอบบอร์ด **SKU-1015 ESP32 38PIN Breakout Board** ใช้คู่กับ **ESP32-WROOM-32E 38PIN CH340 (SKU-1016-1)** และจอ **TFT IPS 240×240 ST7789**
แฟลชไฟล์เดียวจบ ไม่ต้องติดตั้ง Arduino IDE / PlatformIO

*Designed by Massmore*

---

## ไฟล์ในโฟลเดอร์นี้

| ไฟล์ | รายละเอียด |
|---|---|
| `SKU-1015_ESP32_FactoryTest_merged.bin` | ไฟล์รวม (bootloader + partition table + boot_app0 + app) — แฟลชที่ address **`0x0`** |
| `SHA256SUMS.txt` | checksum สำหรับตรวจว่าไฟล์ดาวน์โหลดครบ |

| รายการ | ค่า |
|---|---|
| MCU | ESP32 (ESP32-WROOM-32E), Flash 4MB |
| Core | Arduino-ESP32 2.0.17 (PlatformIO espressif32 @ 6.9.0) |
| Source | [`PlatformIO/src/SKU_1015_ESP32_FACTORY_TEST`](../PlatformIO/src/SKU_1015_ESP32_FACTORY_TEST) / [`ArduinoIDE/Example_Advance/SKU_1015_ESP32_FACTORY_TEST`](../ArduinoIDE/Example_Advance/SKU_1015_ESP32_FACTORY_TEST) |

---

## 1. การแฟลชเฟิร์มแวร์

> เสียบ ESP32 (SKU-1016-1) บนบอร์ด SKU-1015 แล้วต่อ USB เข้าคอมพิวเตอร์ (ต้องติดตั้ง [Driver CH340](https://www.wch-ic.com/downloads/CH341SER_EXE.html) ก่อน)

### วิธีที่ 1: Web Flasher (ไม่ต้องติดตั้งโปรแกรม)

1. เปิด <https://espressif.github.io/esptool-js/> ด้วย **Chrome** หรือ **Edge**
2. Baudrate เลือก `921600` → กด **Connect** → เลือกพอร์ตของบอร์ด
3. Flash Address ใส่ `0x0` → เลือกไฟล์ `SKU-1015_ESP32_FactoryTest_merged.bin`
4. กด **Program** รอจนเสร็จ แล้วกดปุ่ม **EN** บนบอร์ด ESP32

### วิธีที่ 2: esptool (macOS / Linux / Windows)

```bash
pip3 install esptool
esptool --chip esp32 --port /dev/cu.usbserial-XXXX --baud 921600 write-flash 0x0 SKU-1015_ESP32_FactoryTest_merged.bin
```

Windows ใช้ `--port COM5` · esptool รุ่นเก่า (v4) ใช้ `esptool.py ... write_flash` แทน `write-flash`

> - ถ้าแฟลชไม่เข้า: กด **BOOT ค้าง → กด EN → ปล่อย EN → ปล่อย BOOT** แล้วลองใหม่
> - ถ้าแฟลชไม่นิ่ง ลด baud เป็น `460800`

### วิธีที่ 3: Flash Download Tool (Windows)

[ESP Flash Download Tool](https://www.espressif.com/en/support/download/other-tools) → ChipType `ESP32` → เลือกไฟล์ `.bin` ที่ address `0x0` → SPI SPEED 40MHz, SPI MODE DIO → START

---

## 2. การทดสอบ

ต่อไฟ **DC IN 6–12V** เข้าบอร์ด (จำเป็นสำหรับ Servo และ Motor) แล้วกด **EN** — จอแสดงหัว `MASSMORE TEST KIT`
กดปุ่ม **SW (GPIO36)** เพื่อเปลี่ยนหน้า วนกลับหน้าแรกเมื่อจบหน้า 3

| หน้า | สิ่งที่ทดสอบ | วิธีตรวจ |
|---|---|---|
| **1: SENSORS TEST** | IO1–IO7 (GPIO25, 13, 12, 14, 15, 5, 35) | IO1–5, IO7 แสดงค่า Analog 0–4095 + แถบกราฟ · IO6 (GPIO5) แสดงค่า Digital 0/1 (แถบสีม่วง) — ป้อนแรงดัน 0–3.3V ทีละช่องแล้วดูค่าเปลี่ยน |
| **2: VR & SERVOS** | VR (GPIO34), SW (GPIO36), Servo 1–3 (GPIO19, 32, 33) | หมุน VR → ค่า 0–4095 และ Servo ทั้ง 3 ตัวหมุน 0–180° ตาม · กด SW ค่า SW State เป็น 0 |
| **3: MOTOR TEST** | Motor 2 ช่องผ่านโมดูล TB67H450 / TB6612 | มอเตอร์วนรอบละ 2 วินาที: FORWARD → STOP → REVERSE → STOP |

> มอเตอร์หยุดอัตโนมัติทุกครั้งที่กดเปลี่ยนหน้า
> ขา Motor ในโปรแกรมนี้: CH A = GPIO16/17, CH B = GPIO27/26

---

## 3. ตรวจสอบไฟล์ (ไม่บังคับ)

```bash
shasum -a 256 -c SHA256SUMS.txt        # macOS / Linux
certutil -hashfile SKU-1015_ESP32_FactoryTest_merged.bin SHA256   # Windows
```

## 4. Build ไฟล์ใหม่จาก source

```bash
cd PlatformIO
pio run -e factory_test
esptool.py --chip esp32 merge_bin -o ../firmware/SKU-1015_ESP32_FactoryTest_merged.bin \
  --flash_mode dio --flash_freq 40m --flash_size 4MB \
  0x1000 .pio/build/factory_test/bootloader.bin \
  0x8000 .pio/build/factory_test/partitions.bin \
  0xe000 ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin \
  0x10000 .pio/build/factory_test/firmware.bin
```
