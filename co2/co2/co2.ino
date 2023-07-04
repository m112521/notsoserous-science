#include "Adafruit_CCS811.h"
constexpr auto pinSensor = A0;
 
Adafruit_CCS811 ccs;
 
void setup() {
  Serial.begin(9600);
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
}
 
void loop() {
  int valueSensor = analogRead(pinSensor);
  if(ccs.available()) {
    if(!ccs.readData()) {
      Serial.print(ccs.geteCO2());
      Serial.print(",");
      Serial.print(ccs.getTVOC());
      Serial.print(",");
      Serial.println(valueSensor);
    } else {
      Serial.println("ERROR...");
      while(1);
    }
  }
  delay(500);
}