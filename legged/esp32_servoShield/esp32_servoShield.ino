#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 12;
int servoPin2 = 18;
int servoPin3 = 19;
int servoPin4 = 14;


int freePin = 13;



void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  myservo.attach(servoPin2, 500, 2400);
  myservo.attach(servoPin3, 500, 2400);
  myservo.attach(servoPin4, 500, 2400);
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep

  myservo.write(0);    // tell servo to go to position in variable 'pos'
  myservo2.write(0);
  myservo3.write(0);
  myservo4.write(0);

  delay(5000);
}

void loop() {
	for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    myservo3.write(pos);
    myservo4.write(pos);
		delay(5);             // waits 15ms for the servo to reach the position
	}
	for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		myservo.write(pos);
    myservo2.write(pos);
    myservo3.write(pos);
    myservo4.write(pos);   // tell servo to go to position in variable 'pos'
		delay(5);             // waits 15ms for the servo to reach the position
	}
}
