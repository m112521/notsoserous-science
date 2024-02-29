#include <Servo.h>
#define SPEED_1      5 
#define DIR_1        4

Servo myservo;
int command = '0';

void setup(){
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(90);

  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
}

void loop(){
    digitalWrite(DIR_1, LOW);
    analogWrite(SPEED_1, 255); 

    if (Serial.available() > 0) {
      command = (Serial.read()); 
      switch (command) {
        case '0': {
          myservo.write(0);
          break;
        }
        case '1': {
          myservo.write(180);
          break;
        }
      }
    }
}