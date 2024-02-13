#include "CurieIMU.h"
#include <MadgwickAHRS.h>

Madgwick filter;
int factor = 800;

int ax, ay, az, gx, gy, gz;
volatile float yaw, pitch, roll;


void setup() {
  CurieIMU.begin();
  CurieIMU.setAccelerometerRange(2);

  CurieIMU.autoCalibrateGyroOffset();
  Serial.println(" Done");  
  Serial.print("Starting Acceleration calibration...");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);

  Serial.begin(9600);
}

void loop() {
  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz); 
  filter.updateIMU(gx / factor, gy / factor, gz / factor, ax, ay, az);
  yaw = filter.getYaw();
  pitch = filter.getPitch();
  roll = filter.getRoll();

  if (roll > 100) {
    //tone(8, 1024, 100);
    //delay(100);
    Serial.println("Left");
  }
  else if (roll < -50) {
    Serial.println("Right");
  }
  else if (roll > -5 && roll < 5) {
    Serial.println("Center");
  }
}