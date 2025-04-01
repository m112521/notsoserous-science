/* XIAO_ROCKET CODE */
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP32Servo.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define SERVO1_PIN D0

Servo servo1;
String success;

Adafruit_BME280 bme; // I2C
int incomingServo = 0;

// Reciever:
uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x2D, 0xD4, 0x8C};

typedef struct struct_message {
    int altitude;
    int temp;
    int hum;
    int pres;
} struct_message;

typedef struct struct_received {
    int servo;
} struct_received;

struct_message BME280Readings;
struct_received incomingReadings;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingServo = incomingReadings.servo;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

}

void loop() {
  BME280Readings.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  BME280Readings.temp = bme.readTemperature();
  BME280Readings.hum = bme.readHumidity();
  BME280Readings.pres = bme.readPressure() / 100.0F;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &BME280Readings, sizeof(BME280Readings));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  servo1.write(incomingServo);

  delay(1000);
}

