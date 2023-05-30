#define HALL_PIN 7

volatile unsigned long count = 0;

void setup() {
  pinMode(HALL_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), countCycles, RISING);
  Serial.begin(9600);
}

void loop() {
  Serial.println(count);
}

void countCycles() {
  count++;
}


