// Rocket
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define SERVO1_PIN D0

Servo servo1;

Adafruit_BME280 bme; // I2C
unsigned long delayTime;

//CC:DB:A7:2D:D4:8C
uint8_t broadcastAddress1[] = {0xCC, 0xDB, 0xA7, 0x2D, 0xD4, 0x8C};

typedef struct data_struct {
  int altitude;
} data_struct;

data_struct data;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  while(!Serial);    // time to get serial running
  Serial.println(F("BME280 test"));
  bme.begin(0x76);  
  delayTime = 1000;

  servo1.attach(SERVO1_PIN);

  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println();
}


void loop() { 
  printValues();
  data.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  esp_err_t result = esp_now_send(0, (uint8_t *) &data, sizeof(data));
   
  servo1.write(0);
  delay(delayTime);
  servo1.write(180);
  delay(1000);
}


void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}
