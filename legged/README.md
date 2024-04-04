# Legged servo bot

![photo_5391076090363107465_y](https://github.com/m112521/notsoserous-science/assets/85460283/194b444e-faa5-475c-a7ba-40270d74ce5b)

### ESP32 ServoShield

![pcb](https://github.com/m112521/notsoserous-science/assets/85460283/6bd172e2-5d91-4516-843a-040517341e50)



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

