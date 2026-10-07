#include <ESP32Servo.h>

#define VR_PIN 34      // ขาอ่านค่า VR (Potentiometer)
#define SW_PIN 36      // ขาอ่านค่าสวิตช์
#define LED_PIN 2      // ขา LED
#define SERVO1_PIN 19  // ขา Servo 1
#define SERVO2_PIN 32  // ขา Servo 2

Servo servo1, servo2;
bool ledState = false;
bool lastButtonState = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(VR_PIN, INPUT);
    pinMode(SW_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);
}

void loop() {
    // อ่านค่าจาก VR และแปลงเป็นองศา (0 - 180)
    int vrValue = analogRead(VR_PIN);
    int angle = map(vrValue, 0, 4095, 0, 180);
    
    // ควบคุมเซอร์โว
    servo1.write(angle);
    servo2.write(180 - angle);
    
    // อ่านค่าจากสวิตช์
    bool buttonState = digitalRead(SW_PIN);
    
    // เช็คการเปลี่ยนแปลงของปุ่มเพื่อทำ Toggle
    if (buttonState == LOW && lastButtonState == HIGH) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        delay(200); // กันสัญญาณกดเด้ง (Debounce)
    }
    lastButtonState = buttonState;
    
    // แสดงค่าผ่าน Serial Monitor
    Serial.print("VR Volume: ");
    Serial.print(vrValue);
    Serial.print(" | Servo Angle: ");
    Serial.print(angle);
    Serial.print(" | SW State: ");
    Serial.println(buttonState ? "HIGH" : "LOW");
    
    delay(100);
}
