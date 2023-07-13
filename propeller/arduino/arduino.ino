#include <Servo.h>

Servo ESC;
int potValue; 

void setup() {
  ESC.attach(9, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop() {
  potValue = analogRead(A0);
  potValue = map(potValue, 0, 1023, 0, 180);
  ESC.write(potValue);
}
