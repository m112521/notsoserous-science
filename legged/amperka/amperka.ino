#include <Multiservo.h>
 
Multiservo multiservo1;
Multiservo multiservo2;
Multiservo multiservo3;
Multiservo multiservo4;


constexpr uint8_t MULTI_SERVO1_PIN = 6;
constexpr uint8_t MULTI_SERVO2_PIN = 7;
constexpr uint8_t MULTI_SERVO3_PIN = 8;
constexpr uint8_t MULTI_SERVO4_PIN = 9;

int forward = 135;
int backward = 45;
int stop = 0;
 
void setup() {
  multiservo1.attach(MULTI_SERVO1_PIN);
  multiservo2.attach(MULTI_SERVO2_PIN);
  multiservo3.attach(MULTI_SERVO3_PIN);
  multiservo4.attach(MULTI_SERVO4_PIN);
}
 
void loop() {
    multiservo1.write(forward);
    multiservo2.write(forward);
    delay(3000);
    multiservo1.write(backward);
    multiservo2.write(backward);
    delay(3000);
    multiservo1.write(stop);
    multiservo2.write(stop);
    delay(2000);
}
