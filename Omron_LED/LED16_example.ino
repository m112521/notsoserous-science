#include <Adafruit_NeoPixel.h>

#define MATRIX_PIN 8
#define LED_COUNT 16

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(LED_COUNT, MATRIX_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  matrix.begin();
}

void loop(){
  //colorWipe(matrix.Color(random(0,255), random(0,255), random(0,255)), 100);
  //colorWipe(matrix.Color(0, 0, 0), 0);
  colorWipe(matrix.Color(0, 0, 0), 500);
  colorWipe(matrix.Color(255, 0, 0), 500);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < matrix.numPixels(); i++) {
    matrix.setPixelColor(i, c);
    matrix.show();
  }
  delay(wait);
}