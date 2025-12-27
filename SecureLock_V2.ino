#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h> 
#include <MFRC522.h>

// 1. Hardware Initialization
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;
MFRC522 rfid(5, 15); 

// 2. Specific UIDs from the Serial Monitor
byte myCard[]     = {0x62, 0x01, 0xBB, 0x5C}; 
byte myKeychain[] = {0x15, 0x79, 0xF0, 0x05};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  
  lcd.init();
  lcd.backlight();
  
  myServo.setPeriodHertz(50);
  myServo.attach(4, 500, 2400); 
  myServo.write(0); // Ensure locked position
  
  displayLocked();
}

void loop() {
  // Check for Virtual PIN on Serial Monitor
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "1234") unlockSequence("VIRTUAL PIN");
  }

  // Check for Physical RFID Scan
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (checkUID(myCard)) {
      unlockSequence("CARD ACCESS");
    } 
    else if (checkUID(myKeychain)) {
      unlockSequence("KEYCHAIN KEY");
    } 
    else {
      lcd.clear();
      lcd.print("ACCESS DENIED");
      lcd.setCursor(0, 1);
      lcd.print("Unknown User");
      delay(2000);
      displayLocked();
    }
    rfid.PICC_HaltA();
  }
}

// Logic to compare scanned UID with our saved keys
bool checkUID(byte target[]) {
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != target[i]) return false;
  }
  return true;
}

void unlockSequence(String user) {
  lcd.clear();
  lcd.print("ACCESS GRANTED");
  lcd.setCursor(0, 1);
  lcd.print(user);
  
  myServo.write(90); // Move motor to unlock
  delay(5000);       // Stay open for 5 seconds
  myServo.write(0);  // Relock
  
  displayLocked();
}

void displayLocked() {
  lcd.clear();
  lcd.print("SECURE LOCK V2");
  lcd.setCursor(0, 1);
  lcd.print("Scan to Unlock");
}