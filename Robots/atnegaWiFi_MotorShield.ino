#include <Servo.h>

// #define R_LED 4
// #define G_LED 5
// #define B_LED 6

#define SPEED_1      5 
#define DIR_1        4
#define SPEED_2      6
#define DIR_2        7

#define SERVO 9

Servo myservo;

void setup() {
  Serial.begin(115200);

  pinMode(SPEED_1, OUTPUT);
  pinMode(DIR_1, OUTPUT);
  pinMode(SPEED_2, OUTPUT);
  pinMode(DIR_2, OUTPUT);

  myservo.attach(9);
  myservo.write(90);
}

void loop() {
  if(Serial.available()>0) {
    int val = Serial.parseInt();

    if (val == 5) { // Forward
      digitalWrite(DIR_1, HIGH); // set direction
      analogWrite(SPEED_1, 255); // set speed

      digitalWrite(DIR_2, LOW); // set direction
      analogWrite(SPEED_2, 255); // set speed

      // analogWrite(RGB, 255);
      // analogWrite(G_LED, 255);
      // analogWrite(B_LED, 255);
      // Serial.println(val);
    }
    else if (val == 6) { // Stop
      analogWrite(SPEED_1, 0); // set speed
      analogWrite(SPEED_2, 0); // set speed

      // analogWrite(R_LED, 0);
      // analogWrite(G_LED, 120);
      // analogWrite(B_LED, 120);
      // Serial.println(val);
    }
    else if (val == 7) { // Left
      digitalWrite(DIR_1, LOW); // set direction
      analogWrite(SPEED_1, 255); // set speed

      digitalWrite(DIR_2, LOW); // set direction
      analogWrite(SPEED_2, 255); // set speed
      // analogWrite(R_LED, 0);
      // analogWrite(G_LED, 255);
      // analogWrite(B_LED, 0);
      // Serial.println(val);
    }
    else if (val == 8) { // Right
      digitalWrite(DIR_1, HIGH); // set direction
      analogWrite(SPEED_1, 255); // set speed

      digitalWrite(DIR_2, HIGH); // set direction
      analogWrite(SPEED_2, 255); // set speed
      // analogWrite(R_LED, 0);
      // analogWrite(G_LED, 0);
      // analogWrite(B_LED, 255);
      // Serial.println(val);
    }
    else if (val == 9) { // Backward
      digitalWrite(DIR_1, LOW); // set direction
      analogWrite(SPEED_1, 255); // set speed

      digitalWrite(DIR_2, HIGH); // set direction
      analogWrite(SPEED_2, 255); // set speed
      // analogWrite(R_LED, 255);
      // analogWrite(G_LED, 120);
      // analogWrite(B_LED, 0);
      // Serial.println(val);
    }
    else if (val == 4) { // Servo
      myservo.write(180);
    }
    else if (val == 3) { // Servo
      myservo.write(0);
    }
    
  }
}
