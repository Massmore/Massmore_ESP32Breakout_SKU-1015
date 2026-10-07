// ============================================================
//  SKU-1015 ESP32 Breakout Board — 08 DC Motor Basic
//  ควบคุมมอเตอร์ 2 ช่องผ่านโมดูล TB6612FNG / TB67H450
//  M1_IN1=GPIO27, M1_IN2=GPIO26, M2_IN1=GPIO16, M2_IN2=GPIO17
//  ⚠️ ต้องต่อไฟ DC IN 6-12V และเสียบโมดูล Motor Driver ก่อนใช้งาน
// ============================================================

#define M1_IN1 27
#define M1_IN2 26
#define M2_IN1 16
#define M2_IN2 17

// PWM (ESP32 core 2.x)
#define PWM_FREQ 1000
#define PWM_RES  8

void motorSetup() {
  ledcSetup(0, PWM_FREQ, PWM_RES); ledcAttachPin(M1_IN1, 0);
  ledcSetup(1, PWM_FREQ, PWM_RES); ledcAttachPin(M1_IN2, 1);
  ledcSetup(2, PWM_FREQ, PWM_RES); ledcAttachPin(M2_IN1, 2);
  ledcSetup(3, PWM_FREQ, PWM_RES); ledcAttachPin(M2_IN2, 3);
}

// ควบคุมมอเตอร์: motor=1-2, speed=-255..255 (ลบ = ถอยหลัง)
void motorControl(int motor, int speed) {
  speed = constrain(speed, -255, 255);
  int chA = (motor == 1) ? 0 : 2;
  int chB = (motor == 1) ? 1 : 3;
  if (speed >= 0) { ledcWrite(chA, speed);  ledcWrite(chB, 0); }
  else            { ledcWrite(chA, 0);      ledcWrite(chB, -speed); }
}

void stopAll() { motorControl(1, 0); motorControl(2, 0); }

void setup() {
  Serial.begin(115200);
  motorSetup();
  Serial.println("DC Motor Test Start!");
}

void loop() {
  Serial.println("Forward (Speed 200)");
  motorControl(1, 200); motorControl(2, 200);
  delay(2000);

  Serial.println("Stop");
  stopAll();
  delay(1000);

  Serial.println("Reverse (Speed 200)");
  motorControl(1, -200); motorControl(2, -200);
  delay(2000);

  Serial.println("Turn (M1 Forward, M2 Reverse)");
  motorControl(1, 200); motorControl(2, -200);
  delay(1500);

  Serial.println("Stop");
  stopAll();
  delay(1000);
}
