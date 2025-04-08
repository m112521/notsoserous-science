/* RECEIVER_JOYSTICK CODE */
#include <esp_now.h>
#include <WiFi.h>

// XIAO_USED: 
// XIAO_NOT_USED: 64:E8:33:80:89:18
// XIAO_NEW: 
uint8_t broadcastAddress[] = {0x64, 0xE8, 0x33, 0x80, 0xA7, 0x80};


int incomingAltitude;
int incomingTemp;
int incomingHum;
int incomingPres;

String success;

typedef struct struct_received {
    int altitude;
    int temp;
    int hum;
    int pres;
} struct_received;

typedef struct struct_message {
    int servo;
} struct_message;

struct_message servoReadings;
struct_received incomingReadings;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  //Serial.print("Bytes received: ");
  //Serial.println(len);
  
  incomingAltitude = incomingReadings.altitude;
  incomingTemp = incomingReadings.temp;
  incomingHum = incomingReadings.hum;
  incomingPres = incomingReadings.pres;
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
  int ptr = map(analogRead(35), 0, 4095, 0, 180);
  if (ptr >= 100) {
    servoReadings.servo = 180;
  }
  else if (ptr > 50 && ptr < 130) {
    servoReadings.servo = 90;
  }
  else {
    servoReadings.servo = 0;
  }
  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &servoReadings, sizeof(servoReadings));
   
  // if (result == ESP_OK) {
  //   Serial.println("Sent with success");
  // }
  // else {
  //   Serial.println("Error sending the data");
  // }

  printValues();
  //delay(100);
}

void printValues() {
  // Serial.print("Temperature = ");
  // Serial.print(incomingReadings.temp);
  // Serial.println(" °C");

  // Serial.print("Pressure = ");

  // Serial.print(incomingReadings.pres);
  // Serial.println(" hPa");

  // Serial.print("Humidity = ");
  // Serial.print(incomingReadings.hum);
  // Serial.println(" %");

  Serial.print("ALTITUDE: ");
  Serial.print(incomingReadings.altitude);
  Serial.println(" m");
}
