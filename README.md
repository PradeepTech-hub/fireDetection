# ESP32 Fire Detection and Notification System

This project is an IoT-based fire detection system using an ESP32 microcontroller. It detects fire using a digital sensor, triggers visual and audible alarms, and sends real-time notifications to a webhook service (Integromat/Make) via Wi-Fi.

---

## Features

- Real-time fire detection using a digital sensor.
- Visual alert using LEDs:
  - LED1: Normal operation indicator.
  - LED2: Fire alert indicator.
- Audible alert using a buzzer when fire is detected.
- Automated notification sent to Integromat (Make) webhook.
- Prevents repeated notifications during sustained fire conditions.

---

## Hardware Required

- ESP32 Development Board
- Fire/Flame Sensor (digital output)
- Buzzer
- LEDs (2x)
- Resistors (for LEDs if needed)
- Jumper wires
- Breadboard

---

## Pin Configuration

| Component | ESP32 Pin |
|-----------|-----------|
| LED1      | 19        |
| LED2      | 22        |
| Buzzer    | 18        |
| Sensor    | 23        |
| Built-in LED | 2      |

---

## Software Required

- Arduino IDE or VS Code with Arduino extension
- ESP32 board support installed
- Wi-Fi network credentials
- Integromat (Make) webhook URL

---

## Installation

1. Clone the repository:
   
