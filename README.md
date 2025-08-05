# NightGuard - Time-Controlled Motion Detection & Alarm System

A motion-triggered buzzer system that activates only during night hours. It utilises a real-time clock (DS3231), a PIR motion sensor, a keypad password for deactivation, and an OLED display for feedback.

---

## 🔐 Features
- Triggers alarm only between 10 PM and 5 AM
- Requires a 6-digit password to deactivate
- User can enter '#' to reset input
- Displays time and messages on OLED screen
- Cooldown period after successful disarm
- Designed for veroboard or PCB

---

## 🧰 Components Used

| Component              | Description                          |
|------------------------|--------------------------------------|
| Arduino Nano           | Microcontroller                      |
| DS3231 RTC Module      | Real-Time Clock for time control     |
| PIR Sensor (HC-SR501)  | Motion detection                     |
| 1.3" OLED Display      | Displays time and status             |
| Active Buzzer          | Audible alarm output                 |
| 4x3 Matrix Keypad      | Password input                       |
| BC547 NPN Transistor   | Drives the buzzer                    |
| 1kΩ Resistor           | Base resistor for transistor         |
| 2 x 18650 Li-ion Cells | Power source                         |
| Slide Switch           | Manual ON/OFF control                |

---

## ⚙️ How It Works
1. Motion is detected at night → alarm activates.
2. User enters password on keypad.
3. If correct → alarm stops + cooldown begins.
4. OLED displays live time and system status.

---

## ⚡ PCB & Schematic
- [Schematic](Schematic_NightGuard.png)
- [PCB TopView Layout](images/NightGuard_PCB_TopView.png)
- [PCB BottomView Layout](images/NightGuard_PCB_BottomView.png)

---

## ⚖️ License

This project is licensed under the [MIT License](LICENSE).

---

## 📖 References

- [Arduino StackExchange DS3231 Example](https://arduino.stackexchange.com/questions/93880/)
- [ElectroPeak 4x3 Keypad Guide](https://electropeak.com/learn/interfacing-4x3-membrane-matrix-keypad-with-arduino/?srsltid=AfmBOooRHeVJUqyHZ-mqR8IOUq6pQYcNW9BYw03qPwAUB0oAoLDEjowV)

---

## 👤 Author

*Muhammad Sami*  
Electronics & Embedded Systems Enthusiast | Electrical Engineering Undergrad

---
