#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;

String secretPIN = "1234";

void setup() {
  Serial.begin(115200);
  
  // LCD Init
  lcd.init();
  lcd.backlight();
  
  // Servo Init
  myServo.attach(13); // Signal on D13
  myServo.write(0);   // Start in 'Locked' position (0 degrees)
  
  lcd.setCursor(0, 0);
  lcd.print("SERVO LOCK READY");
  lcd.setCursor(0, 1);
  lcd.print("Enter PIN on PC");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    lcd.clear();
    if (input == secretPIN) {
      lcd.print("ACCESS GRANTED");
      lcd.setCursor(0, 1);
      lcd.print("Unlocking...");
      
      myServo.write(90);  // MOVE THE MOTOR 90 DEGREES
      delay(3000);        // Keep it open for 3 seconds
      myServo.write(0);   // RELOCK
      
      lcd.clear();
      lcd.print("Locked Again.");
    } else {
      lcd.print("ACCESS DENIED");
      lcd.setCursor(0, 1);
      lcd.print("Incorrect PIN");
    }
    
    delay(2000);
    lcd.clear();
    lcd.print("Enter PIN on PC");
  }
}
