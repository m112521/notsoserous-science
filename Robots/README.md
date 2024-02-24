# Servo Feeder

BOM:

- Mg995
- Arduino Uno
- RGB LED
- *Buzzer

![Assembly](Assembly.jpg)


Code (with buzzer):
```c++
#include <RTClib.h>
#include <Wire.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define MATRIX_PIN 7
#define LED_COUNT 7

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(LED_COUNT, MATRIX_PIN, NEO_GRB + NEO_KHZ800);

Servo myservo; 
int pos = 0;   


int R = 210;
int G = 255;
int B = 0;

RTC_DS3231 rtc;
char t[32];

void setup()
{
  myservo.attach(9);
  myservo.write(0); 
  pinMode(MATRIX_PIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));

  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); // set time to Saturday 8:29:00am Jan 1 2011
  Alarm.timerRepeat(15, Repeats);
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < matrix.numPixels(); i++) {
    matrix.setPixelColor(i, c);
  }
  matrix.show();
  delay(wait);
}


void Repeats() {
  Serial.println("15 second timer");
  
  
  tone(5, 512, 5000);
  colorWipe(matrix.Color(R, G, B), 5000);
  delay(3000);
  colorWipe(matrix.Color(0, 0, 0), 1);
  openLid();
}

void MorningAlarm() {
  Serial.println("Alarm: - turn lights off");
}

void WeeklyAlarm() {
  Serial.println("Alarm: - its Monday Morning");
}

void openLid() {
  
  myservo.write(90);              
  delay(1000);                    
  myservo.write(0);            
  delay(10);                       
}

void loop()
{
  Alarm.delay(1000);
}
```