#define M1 A0
#define M2 A2
#define M3 A4
 
void setup() {
  Serial.begin(9600);
  pinMode(M1, INPUT);
  pinMode(M2, INPUT);
  pinMode(M3, INPUT);
  
}
 
void loop() {
  Serial.print(analogRead(M1));
  Serial.print(",");
  Serial.print(analogRead(M2));
  Serial.print(",");
  Serial.println(analogRead(M3));
  delay(3000);
}