/*
  ledcWrite_RGB.ino
  Runs through the full 255 color spectrum for an rgb led
  Demonstrate ledcWrite functionality for driving leds with PWM on ESP32
  This example code is in the public domain.
  Some basic modifications were made by vseven, mostly commenting.
*/
// Motor
int motor1Pin1 = 16;
int motor1Pin2 = 17;
int motor2Pin1 = 27;
int motor2Pin2 = 26;

// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(115200);
  delay(10);

  ledcAttachPin(motor1Pin1, 1); // assign RGB led pins to channels
  ledcAttachPin(motor1Pin2, 2);
  ledcAttachPin(motor2Pin1, 3);
  ledcAttachPin(motor2Pin2, 4);

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);
  ledcSetup(4, 12000, 8);

  Serial.print("Testing DC Motor...");
}
// void loop runs over and over again
void loop()
{
    // Stop the DC motor
  Serial.println("Motor stopped");
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
  delay(1000);
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  ledcWrite(1, 255);
  ledcWrite(2, 0);
  ledcWrite(3, 255);
  ledcWrite(4, 0);
  delay(3000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  ledcWrite(1, 0);
  ledcWrite(2, 255);
  ledcWrite(3, 0);
  ledcWrite(4, 255);
  delay(3000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
  delay(1000);
  
  // Stop the DC motor
  Serial.println("Motor Speed+");
  ledcWrite(1, 100);
  ledcWrite(2, 0);
  ledcWrite(3, 100);
  ledcWrite(4, 0);
  delay(1000);

    // Stop the DC motor
  Serial.println("Motor Speed+");
  ledcWrite(1, 125);
  ledcWrite(2, 0);
  ledcWrite(3, 125);
  ledcWrite(4, 0);
  delay(1000);

    // Stop the DC motor
  Serial.println("Motor Speed+");
  ledcWrite(1, 200);
  ledcWrite(2, 0);
  ledcWrite(3, 200);
  ledcWrite(4, 0);
  delay(1000);

  
    // Stop the DC motor
  Serial.println("Motor Speed+");
  ledcWrite(1, 255);
  ledcWrite(2, 0);
  ledcWrite(3, 255);
  ledcWrite(4, 0);
  delay(1000);

}
