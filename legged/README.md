# Legged servo bot


### Amperka MultiServo Shield

1. Install lib MultiServo

```c++
int forw = 135;
int backw = 45;
int stop = 0;

```

### PCA9685

1. Install lib Adafruit-PWM-Servo-Driver-Library

2. For 360 servo:

```c++
pwm.setPWM(servoIdx, 0, dir); //dir = 150 or 600
```

3. For 180 servo:

```c++
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);

```

