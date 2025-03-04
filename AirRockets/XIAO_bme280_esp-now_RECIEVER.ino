// Reciever
#include <esp_now.h>
#include <WiFi.h>


typedef struct test_struct {
  int altitude = 0;
} test_struct;

test_struct rocket;


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&rocket, incomingData, sizeof(rocket));
  Serial.println(String(rocket.altitude) + " " + "m");  
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Serial.print("Apprx. altitude: ");
  Serial.print(rocket.altitude);
  Serial.println("m");

}