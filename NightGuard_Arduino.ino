/*
  Title: NightGuard: Time Controlled Motion Detection & Alarm System
  Author: Muhammad Sami
  Description:
    - Detects motion via a PIR sensor
    - Alarm triggered when sensor detects motion between 10PM and 5AM
    - Sounds buzzer until user enters correct password via 4x3 keypad
    - OLED to display real-time, key messages, results and a cooldown timer 

  Hardware:
    - Arduino Nano
    - DS3231 RTC Module
    - PIR Sensor
    - Buzzer
    - OLED Display 128x64 (I2C)
    - 4x3 Matrix Keypad
    - BC547 - NPN Transistor
    - Slide Switch
    - 1k ohm resistor

  Skills:
    - Time-based logic
    - Keypad input handling
    - OLED display via U8glib
    - Real-time clock integration
    - CoolDown design
*/

#include <Keypad.h>
#include <U8glib.h>
#include <RTClib.h>
#include <Wire.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

// Initialize the RTC module and declare variables to store time
RTC_DS3231 rtc;
int hours, minutes, seconds;

// Initializing GPIO pins and the variables used
String Result_Message = "";
String Key_Message = "";
const int BUZZER = 3, VCC_aux = 4, PIR = 5;
int pir_status;
bool Alarm_Triggered = false, coolDown;

// Define the isNight function to check if the current time is between 10PM and 5AM
bool isNight () {
  return (hours >= 22 || hours <= 5);
}

// Define the displayTime function to display the current time on the OLED screen
void displayTime() {
  u8g.setPrintPos(5, 55);
  if (hours < 10) u8g.print("0");
  u8g.print(hours);
  u8g.print(":");
  if (minutes < 10) u8g.print("0");
  u8g.print(minutes);
  u8g.print(":");
  if (seconds < 10) u8g.print("0");
  u8g.print(seconds);
}

/*
Define the getTime function to retrieve the current time from the RTC module and store it in the hour, minute, and second variables.
Prevents time update pause during the cool-down period.
*/
void getTime() {
  DateTime now = rtc.now();
  hours = now.hour();
  minutes = now.minute();
  seconds = now.second();
}

// Initialize keypad settings and define the correct password sequence
const byte ROWS = 4;
const byte COLS = 3;
char const password[6] = {'5', '7', '*', '2', '7', '3'};
char entered[6];
int index = 0;
char keys[ROWS][COLS] {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = {11, 6, 7, 9};
byte colPins[COLS] = {10, 12, 8};  
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  rtc.begin();
  u8g.setFont(u8g_font_unifont);

  // Uncomment during first upload then recomment during next upload to prevent synchronization issues
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(VCC_aux, OUTPUT);
  digitalWrite(VCC_aux, HIGH);
}

void loop() {
  getTime();
  pir_status = digitalRead(PIR);
  // Displays the PIR status - for debugging
  Serial.println(pir_status);

  // Trigger alarm when the PIR sensor detects motion and the time is between 10PM and 5AM
  if (pir_status == HIGH && isNight()) {
    Alarm_Triggered = true;
    tone(BUZZER, 1000);
  }

  if (Alarm_Triggered) {
    // Handle key input from the keypad
    char key = keypad.getKey();

    // Prevents unnecessary display changes when no key is pressed
    if (key != NO_KEY) {
      Key_Message = "You entered: ";

      // '#' used to restart keying in and prevent keypad issues
      if (key == '#') {
        Result_Message = "User Abort";
        index = 0;
      } else {
        entered[index] = key; 
        index++;
        Key_Message += key;
        Result_Message = " ";
      }

      // Executes when the user has entered a complete 6 digit password
      if (index == 6) {
        bool match = true;
        for(int n = 0; n < 6; n++) {
          if (entered[n] != password[n]) {
            match = false;
            break;
          }
        }
        index = 0;

        // Empty Key_Message to prevent unnecessary display
        Key_Message = " ";

        // If the entered password matches the stored password, turn off the alarm
        if (match) { 
          Result_Message = "Correct!";
          noTone(BUZZER);
          coolDown = true;
          Alarm_Triggered = false;
        } else {
          Result_Message = "Incorrect!";
        }
      }
    } else {
      // Empty Key_Message and Result_Message to prevent unnecessary display
      Key_Message = " ";
      Result_Message = " ";
    }
  }
  
  // Display the current key input (Key_Message) and result (Result_Message) on the OLED screen
  u8g.firstPage();
  do {
    u8g.setPrintPos(5, 15);
    u8g.print(Key_Message);
    u8g.setPrintPos(5, 35);
    u8g.print(Result_Message);
    displayTime();
  } while(u8g.nextPage());

  // If the correct password is entered, start the cool-down period to prevent the sensor from being triggered again
  if (coolDown) {
    for (int m = 0; m >= 0; m--) {
      for (int s = 59; s >= 0; s--) {
        getTime();
        u8g.firstPage();
        do {
          u8g.setPrintPos(5, 20);
          u8g.print("coolDown period: ");
          u8g.setPrintPos(5, 40);
          u8g.print(m);
          u8g.print("m ");
          u8g.print(s);
          u8g.print("s");
          displayTime();
        } while (u8g.nextPage());
        delay(1000);
      }
    }
    coolDown = false;
    Result_Message = " ";
  }
}