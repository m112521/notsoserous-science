#include <Servo.h>
#define PTR A0

Servo servo;

void setup() {
  servo.attach(8); 
  servo.write(90); 
}

void loop() {
  int val = analogRead(PTR);
  val = map(val, 0, 1023, 0, 180); 
  servo.write(val);
}
