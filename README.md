# NightGuard  
**Time-Controlled Motion Detection & Alarm System**

**NightGuard** is an Arduino-based motion detection system designed for nighttime security. It uses a PIR sensor to detect movement and triggers an audible alarm that can only be silenced with a password entered via a 4x3 matrix keypad.

---

## 🔐 Features

- Motion detection using PIR sensor (HC-SR501)
- Audible alarm via active buzzer when motion is detected
- Alarm is **active only between 12:00 AM and 9:00 AM**
- Alarm **continues to beep until the correct 6-digit password** is entered
- Time-based logic implemented using DS3231 Real-Time Clock (RTC) module

---

## 🧰 Components Used

| Component              | Description                          |
|------------------------|--------------------------------------|
| Arduino Nano           | Microcontroller                      |
| DS3231 RTC Module      | Real-Time Clock for time control     |
| PIR Sensor (HC-SR501)  | Motion detection                     |
| Active Buzzer          | Audible alarm output                 |
| 4x3 Matrix Keypad      | Password input                       |
| BC547 NPN Transistor   | Drives the buzzer                    |
| 1kΩ Resistor           | Base resistor for transistor         |
| 2 x 18650 Li-ion Cells | Power source                         |
| Slider Switch          | Manual ON/OFF control                |

---

## 📦 Project Behavior

1. The system remains idle during the day.
2. Between **12:00 AM and 9:00 AM**, if motion is detected:
   - The buzzer activates continuously.
   - The LED turns on (visual alert).
3. The buzzer continues until the **correct 6-character password** is entered on the keypad.
4. After a successful password, the system silences the alarm and resets.

---

## 📝 Notes

- The RTC should be synced to the correct time before deployment. Uncomment `rtc.adjust(...)` in the code during the first upload.
- Be sure to debounce keypad input in software (already handled in code).

---

## 📚 References & Code Credits

This project reuses logic and code snippets from the following resources:

- [Troubleshooting DS3231 Time Sync Issues](https://arduino.stackexchange.com/questions/93880/)  
- [4x3 Matrix Keypad Arduino Tutorial](https://lastminuteengineers.com/arduino-keypad-tutorial/)

---

## ⚖️ License

This project is licensed under the [MIT License](LICENSE).

---

## 🙋‍♂️ Author

**Muhammad Sami**  
*Electronics & Embedded Systems Enthusiast | Electrical Engineering Undergrad*

---

