// Temp
// RTC
// IMU
/*
Note frequncy: 
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz
*/
#include "CurieIMU.h"
#include <MadgwickAHRS.h>
#include <CurieTime.h>
#include <QuadDisplay2.h>
#include "pitches.h"

#define R_LED 5
#define G_LED 6
#define B_LED 7
float smoothness_pts = 500;//larger=slower change in brightness  
float gammas = 0.14; // affects the width of peak (more or less darkness)
float beta = 0.5; // shifts the gaussian to be symmetric

int lastMin = 0;
int lastHour = 0;

Madgwick filter;
int factor = 800;

int ax, ay, az, gx, gy, gz;
volatile float yaw, pitch, roll;


QuadDisplay qd(9);


int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void playMelody() {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void setup() {
  CurieIMU.begin();
  CurieIMU.setAccelerometerRange(2);

  CurieIMU.autoCalibrateGyroOffset();
  Serial.println(" Done");  
  Serial.print("Starting Acceleration calibration...");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);

  qd.begin();
  playMelody();

  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);

  setTime(12, 0, 0, 06, 02, 2024); // hour, min, sec, day, month, year
  Serial.begin(9600);
}

void displayQuad() {
  qd.displayInt(123);
  qd.displayInt(-123);

  qd.displayInt(12, true);
  qd.displayFloat(-1.23, 2);

  qd.displayTemperatureC(-5);
  qd.displayDigits(QD_O, QD_f, QD_f, QD_NONE); // off
  qd.displayDigits(QD_O, QD_n, QD_NONE, QD_NONE); // on
  qd.displayClear();
}

void ledBounce() {
  for (int ii=0;ii<smoothness_pts;ii++){
    float pwm_val = 255.0*(exp(-(pow(((ii/smoothness_pts)-beta)/gammas, 2.0))/2.0));
    analogWrite(R_LED, pwm_val);
    analogWrite(G_LED, pwm_val);
    analogWrite(B_LED, pwm_val);
    delay(5);
  }
}

void loop() {
  //tone(8, 1024, 100); //pin, freq, duration
  //delay(200);

  // Serial.println(String(hour()) + " " + String(minute()));
  // if (minute() == (lastMin + 1)) {
  //   playMelody();
  //   ledBounce();

  //   lastMin = minute();
  // }

  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz); 
  filter.updateIMU(gx / factor, gy / factor, gz / factor, ax, ay, az);
  yaw = filter.getYaw();
  pitch = filter.getPitch();
  roll = filter.getRoll();

  if (roll > 100) {
    tone(8, 1024, 100);
    delay(100);
  }

  //Serial.println(String(yaw) + " " + String(pitch) + " " + String(roll));
}
