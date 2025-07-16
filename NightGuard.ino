#include <RTClib.h>
#include <Wire.h>
#include <Keypad.h>


// 6-digit password to deactivate the alarm
const char password[6] = {'5', '7', '*', '2', '7', '3'};

char entered[6];
int index = 0;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = { 12, 11, 10, 9 };  // connected to the row pinouts of the keypad
byte colPins[COLS] = { 8, 6, 5 };     // connected to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


RTC_DS3231 rtc;
int hoursNow;
int minutesNow;
int secondsNow;

bool AlarmTriggered;
const int BUZZER = 4;
const int PIR = 7;
const int LED = 13;
int pir_status = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  Wire.begin();
  rtc.begin();
  // Uncomment the line below only during first upload to sync RTC
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  pir_status = digitalRead(PIR);
  DateTime now = rtc.now();
  hoursNow = now.hour();
  minutesNow = now.minute();
  secondsNow = now.second();

  // Debugging via the Serial Monitor
  Serial.print(hoursNow);
  Serial.print(":");
  Serial.print(minutesNow);
  Serial.print(":");
  Serial.print(secondsNow);
  Serial.print("  - ");
  Serial.println(pir_status);

  // Activate buzzer if motion is detected between 12:00 AM and 9:00 AM
  if (pir_status == HIGH && (hoursNow > 23 || hoursNow < 9)){
    tone(BUZZER, 1000);
    digitalWrite(LED, HIGH);
    AlarmTriggered = true;
  }

  if (AlarmTriggered) {
    char key = keypad.getKey();

    if (key != NO_KEY) {
      Serial.print("You pressed: ");
      Serial.println(key);
      entered[index] = key;
      index++;

      if (index == 6) {
        bool match = true;
        for (int i = 0; i < 6; i++) {
          if (entered[i] != password[i]) {
            match = false;
            break;
          }
        }

        if (match) {
          Serial.println("Password correct!");
          noTone(BUZZER);
          AlarmTriggered = false;
          delay(30000);  // 30 second cooldown time to avoid retriggering
        } else {
          Serial.println("Incorrect password.");
        }

        index = 0; // Reset index for next attempt
      }
    }
  }
  delay(50); // Short delay for keypad debounce
}


// 🔗 References:
// - RTC synchronisation method and parts of code adapted from: https://arduino.stackexchange.com/questions/93880/
// - Keypad logic inspired by: https://lastminuteengineers.com/arduino-keypad-tutorial/
