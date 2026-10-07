#include <TFT_eSPI.h>
#include <SPI.h>
#include <ESP32Servo.h>

// ==========================================
// PIN DEFINITIONS
// ==========================================
// Analog Inputs
const int analogPins[7] = {25, 13, 12, 14, 15, 5, 35};
#define VR_PIN 34      
#define SW_PIN 36      
// #define LED_PIN 2   // ชนกับ TFT_DC จึงขออนุญาตปิดไว้เพื่อไม่ให้จอรวน

// Servos
#define SERVO1_PIN 19  
#define SERVO2_PIN 32  
#define SERVO3_PIN 33  

// Motors (TB6612FNG / 2CH)
#define M1_IN1 16
#define M1_IN2 17
#define M2_IN1 27
#define M2_IN2 26

// ==========================================
// OBJECTS & VARIABLES
// ==========================================
TFT_eSPI tft = TFT_eSPI(); 
Servo servo1;
Servo servo2;
Servo servo3;

int currentPage = 0;       // 0: Analog, 1: VR+Servo, 2: Motors
int lastSwState = HIGH;    
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(115200);

  // Init Inputs
  pinMode(SW_PIN, INPUT); // GPIO 36 ไม่มี Internal Pull-up (ต้องพึ่ง Hardware Pull-up บนบอร์ด)
  for(int i=0; i<7; i++) {
    pinMode(analogPins[i], INPUT);
  }
  pinMode(VR_PIN, INPUT);

  // Init Motors
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  stopMotors();

  // Init Servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  // Init TFT
  tft.init();
  tft.setRotation(0); // แนวตั้ง (หรือเปลี่ยนเป็น 1, 2, 3 ตามทิศทางบอร์ด)
  tft.fillScreen(TFT_BLACK);
  
  drawHeader();
}

void loop() {
  handleButton(); // เช็คการกดปุ่มเพื่อเปลี่ยนหน้าจอ

  // แสดงผลตามหน้าจอที่เลือก
  switch(currentPage) {
    case 0:
      runPageAnalog();
      break;
    case 1:
      runPageVR_Servo();
      break;
    case 2:
      runPageMotor();
      break;
  }
  
  delay(50); // หน่วงเวลาเล็กน้อยลดการกระพริบ
}

// ==========================================
// FUNCTIONS
// ==========================================

void handleButton() {
  int swState = digitalRead(SW_PIN);
  // เช็คขอบขาลง (Active Low) และป้องกัน Debounce
  if (swState == LOW && lastSwState == HIGH && millis() - lastDebounceTime > 200) {
    currentPage++;
    if(currentPage > 2) currentPage = 0;
    
    tft.fillScreen(TFT_BLACK); // เคลียร์จอเมื่อเปลี่ยนหน้า
    drawHeader();
    stopMotors(); // หยุดมอเตอร์เมื่อเปลี่ยนหน้า
    lastDebounceTime = millis();
  }
  lastSwState = swState;
}

void drawHeader() {
  tft.fillRect(0, 0, 240, 30, TFT_NAVY);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("MASSMORE TEST KIT", 120, 15, 2);
  tft.setTextDatum(TL_DATUM);
}

// --- หน้า 1: ทดสอบ Analog & Digital ---
void runPageAnalog() {
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  // เปลี่ยนชื่อหัวข้อให้ครอบคลุมทั้ง Analog และ Digital
  tft.drawString("PAGE 1: SENSORS TEST", 10, 40, 2); 
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  for(int i=0; i<7; i++) {
    int pin = analogPins[i];
    int val = 0;
    String prefix = "";
    int barLen = 0;
    uint32_t barColor = TFT_CYAN;

    // เช็คว่าเป็นขา 5 หรือไม่ (ถ้าใช่ให้อ่านเป็น Digital)
    if (pin == 5) {
      val = digitalRead(pin);       // อ่านค่าได้ 0 หรือ 1
      prefix = "D";                 // ใช้ตัวอักษรนำหน้าเป็น D (Digital)
      barLen = (val == HIGH) ? 80 : 0; // ถ้าเป็น 1 (HIGH) ให้กราฟเต็มหลอด
      barColor = TFT_MAGENTA;       // เปลี่ยนสีกราฟเป็นสีม่วงอมชมพูเพื่อแยกให้ชัดเจน
    } else {
      val = analogRead(pin);        // ขาอื่นๆ อ่านค่า Analog ได้ 0-4095
      prefix = "A";                 // ใช้ตัวอักษรนำหน้าเป็น A (Analog)
      barLen = map(val, 0, 4095, 0, 80);
    }

    int yPos = 70 + (i * 22);
    
    // พิมพ์ชื่อพินและค่า (เช่น D6 (G5): 1 หรือ A1 (G25): 4095)
    String text = prefix + String(i+1) + " (G" + String(pin) + "): ";
    char buf[20];
    sprintf(buf, "%-10s %4d", text.c_str(), val);
    tft.drawString(buf, 10, yPos, 2);

    // วาด Bar Graph
    tft.fillRect(140, yPos+2, barLen, 10, barColor);
    tft.fillRect(140+barLen, yPos+2, 80-barLen, 10, TFT_DARKGREY); // ลบแถบที่เหลือ
  }
}

// --- หน้า 2: ทดสอบ VR, SW และ Servos ---
void runPageVR_Servo() {
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("PAGE 2: VR & SERVOS", 10, 40, 2);

  int vrVal = analogRead(VR_PIN);
  int swVal = digitalRead(SW_PIN);
  
  // แปลงค่า VR เป็นองศา 0-180
  int angle = map(vrVal, 0, 4095, 0, 180);
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  
  char buf[30];
  sprintf(buf, "VR Value : %4d   ", vrVal);
  tft.drawString(buf, 10, 80, 4);
  
  sprintf(buf, "SW State : %d      ", swVal);
  tft.drawString(buf, 10, 110, 4);

  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  sprintf(buf, "Servo Angle: %3d deg", angle);
  tft.drawString(buf, 10, 160, 4);
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("* Turn VR to move Servos", 10, 200, 2);
}

// --- หน้า 3: ทดสอบ Motor ---
void runPageMotor() {
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("PAGE 3: MOTOR TEST", 10, 40, 2);

  // วนลูปการทำงานทุกๆ 2 วินาที (เปลี่ยนสเต็ป)
  int step = (millis() / 2000) % 4; 
  String m1State = "";
  String m2State = "";

  switch(step) {
    case 0: // Forward
      digitalWrite(M1_IN1, HIGH); digitalWrite(M1_IN2, LOW);
      digitalWrite(M2_IN1, HIGH); digitalWrite(M2_IN2, LOW);
      m1State = "FORWARD"; m2State = "FORWARD";
      break;
    case 1: // Stop
    case 3: // Stop
      stopMotors();
      m1State = "STOP   "; m2State = "STOP   ";
      break;
    case 2: // Reverse
      digitalWrite(M1_IN1, LOW); digitalWrite(M1_IN2, HIGH);
      digitalWrite(M2_IN1, LOW); digitalWrite(M2_IN2, HIGH);
      m1State = "REVERSE"; m2State = "REVERSE";
      break;
  }

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Motor 1 (CH A):", 10, 80, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(m1State + "    ", 20, 110, 4);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Motor 2 (CH B):", 10, 150, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(m2State + "    ", 20, 180, 4);
}

void stopMotors() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
}