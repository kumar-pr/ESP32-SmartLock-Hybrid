# Multi-Factor Secure Access Control (Phase 2)
**Project Status:** Functional Prototype / Hardware-in-the-Loop (HIL) Testing 
**Current Build:** RFID (SPI) + Virtual Keypad (UART) + Servo Actuation

## 1. Project Overview
This repository documents the evolution of an ESP32-based security system. It has transitioned from a software-simulated keypad to a hardware-integrated system utilizing **RFID (Radio Frequency Identification)** and **PWM-controlled actuation**.

## 2. Phase 2 System Architecture (Current)
The ESP32 manages three concurrent communication protocols to interface with peripherals:

| Peripheral | Protocol | GPIO Pins | Purpose |
| :--- | :--- | :--- | :--- |
| **MFRC522 RFID** | **SPI** | **5, 18, 19, 23, 15** | Token authentication |
| **16x2 LCD** | **I2C** | **21, 22** | Real-time User Feedback |
| **MG90S Servo** | **PWM** | **4** | Mechanical Actuation |



## 3. Engineering Challenges & Debugging
### 3.1 SPI Signal Integrity (Phase 2)
During RFID integration, the system initially returned `Chip Software Version: 0x0` or `0xB2`.
* **Diagnosis:** High-speed SPI data lines (MISO/MOSI) were dropping bits due to loose friction-fit jumper connections.
* **Resolution:** Implemented physical terminal tensioning (wedge-and-tape method) to stabilize contact, achieving a stable **Version 0x92** read.

### 3.2 I2C Bus Management (Phase 1 Archive)
Identified a "Not Acknowledged" (NACK) error during initial LCD deployment.
* **Resolution:** Utilized an I2C scanner script to identify slave address `0x27`.

## 4. Development History (Phase 1 Archive)
* **Objective:** Establish a stable communication bridge between UART input and mechanical actuation.
* **Mechanical Integration:** Engineered a temporary linkage using a screwdriver as a makeshift deadbolt to verify SG90 torque limits (0° to 90°).
* **Logic:** Implemented a conditional state machine for PIN verification via UART (115200 Baud).

## 5. Repository Structure
* **`SecureLock_V1_Serial.ino`**: UART-based authentication logic.
* **`SecureLock_V2_RFID.ino`**: Current stable build with SPI RFID and multi-UID support.

## 6. Future Roadmap
* **Phase 3 (Security Hardening):** Implementation of "Lockout" logic to prevent brute-force attacks.
* **Data Persistence:** Using **EEPROM** to save system states even after power loss.
