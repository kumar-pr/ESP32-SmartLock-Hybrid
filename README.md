# ESP32 Smart Lock System: Phase 1
**Project Status:** Functional Prototype / Hardware-in-the-Loop (HIL) Testing

## 1. Project Overview
This repository contains the firmware and system architecture for a secure locking mechanism based on the ESP32 platform. The primary objective of Phase 1 was to establish a stable communication bridge between user input, visual feedback, and mechanical actuation.

## 2. System Architecture
The system integrates three core subsystems to achieve secure authentication and physical state change:

* **Logic & Processing:** ESP32 (Xtensa® Dual-Core 32-bit LX6).
* **User Interface (Visual):** 16x2 Liquid Crystal Display via I2C protocol (Inter-Integrated Circuit).
* **Actuation:** High-torque SG90 Servo controlled via Pulse Width Modulation (PWM).
* **Virtual Input Layer:** UART Serial communication (115200 Baud) utilized to simulate keypad input during hardware resource constraints.

## 3. Technical Implementation
### 3.1 I2C Bus Management
During initial deployment, a "Not Acknowledged" (NACK) error was detected on the I2C bus.
* **Diagnosis:** Execution of an I2C address scanner script to verify slave device presence.
* **Resolution:** Identified the slave device address at `0x27` and verified physical signal integrity.

### 3.2 Mechanical Integration
To test the torque and rotation limits of the MG90S servo, a temporary mechanical linkage was engineered using a screwdriver as a makeshift deadbolt. This allowed for the verification of the "Locked" vs. "Unlocked" angular positions (0° to 90°).

## 4. Firmware Logic
The firmware utilizes a conditional state machine to handle PIN verification:
1. **Idle State:** System polls for UART Serial data from the host PC.
2. **Buffer Processing:** Received string is trimmed of whitespace and compared against the `secretPIN` constant.
3. **Authentication State:**
    * **Success:** Triggers a 90° PWM signal to the servo and updates the I2C display.
    * **Failure:** Rejects input, updates display with error message, and logs the event to Serial.

## 5. Future Development (Roadmap)
* **Phase 2:** Integration of a 4x4 matrix membrane keypad for standalone physical operation.
* **Phase 3:** Implementation of security "Lockout" logic to prevent brute-force attacks after three failed attempts.
