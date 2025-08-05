# Smart Night-Time Motion Alarm

A motion-triggered buzzer system that activates only during night hours. It utilises a real-time clock (DS3231), a PIR motion sensor, a keypad password for deactivation, and an OLED display for feedback.

## Features
- Triggers alarm only between 10 PM and 5 AM
- Requires a 6-digit password to deactivate
- User can enter '#' to reset input
- Displays time and messages on OLED screen
- Cooldown period after successful disarm
- Designed for veroboard or PCB

## Components Used
- Arduino Nano
- DS3231 RTC module
- HC-SR501 PIR sensor
- 4x3 Matrix Keypad
- 1.3" OLED display (I2C)
- Active Buzzer
- BC547 Transistor
- 1k ohm resistor
- Veroboard/PCB
- Slide Switch

## How It Works
1. Motion is detected at night → alarm activates.
2. User enters password on keypad.
3. If correct → alarm stops + cooldown begins.
4. OLED displays live time and system status.



## PCB & Schematic
- [Schematic](schematic.pdf)
- [PCB TopView Layout](images/NightGuard_PCB_TopView)
- [PCB BottomView Layout](images/NightGuard_PCB_BottomView)

## Author
Muhammad Sami (Electrical Engineering Student, 2025)
