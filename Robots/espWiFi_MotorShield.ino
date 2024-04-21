#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "GalaxyAzamat";
const char* password = "vhrg8328";

bool ledState = 0;
int moveState = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Robot Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    /* box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); */
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    width: 100%;
    height: 7rem;
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 3px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
   .parent {
        display: grid;
        grid-template-columns: repeat(3, 1fr);
        grid-template-rows: repeat(3, 1fr);
        grid-column-gap: 0px;
        grid-row-gap: 0px;
    }

    .div1 { grid-area: 1 / 2 / 2 / 3; padding: 5px;}
    .div2 { grid-area: 2 / 1 / 3 / 2; padding: 5px;}
    .div3 { grid-area: 2 / 2 / 3 / 3; padding: 5px;}
    .div4 { grid-area: 2 / 3 / 3 / 4; padding: 5px;}
    .div5 { grid-area: 3 / 2 / 4 / 3; padding: 5px;}
    </style>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>Robot Control</h1>
  </div>
  <div class="content">
    <div class="card">
      <p class="state">state: <span id="state">%STATE%</span></p>
      <p></p>
      <p></p>
      <p></p>
      <div class="parent">
        <div class="div1"><button id="buttonF" class="button">Forward</button></div>
        <div class="div2"><button id="buttonL" class="button">Left</button></div>
        <div class="div3"><button id="buttonS" class="button">Stop</button></div>
        <div class="div4"><button id="buttonR" class="button">Right</button></div>
        <div class="div5"><button id="buttonB" class="button">Backward</button></div>
        </div>
        <div>
          <button id="servoUp" class="button">UP</button>
          <button id="servoDown" class="button">DOWN</button>
        </div>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    if (event.data == "5"){
      state = "Forward";
    }
    else if(event.data == "6"){
      state = "Stop";
    }
    else if(event.data == "7"){
      state = "Left";
    }
    else if(event.data == "8"){
      state = "Right";
    }
    else if(event.data == "9"){
      state = "Backward";
    }
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('buttonF').addEventListener('click', forwardMove);
    document.getElementById('buttonS').addEventListener('click', stopMove);
    document.getElementById('buttonL').addEventListener('click', leftMove);
    document.getElementById('buttonR').addEventListener('click', rightMove);
    document.getElementById('buttonB').addEventListener('click', backwardMove);
    document.getElementById('servoUp').addEventListener('click', servoUp);
    document.getElementById('servoDown').addEventListener('click', servoDown);
  }
  function servoUp(){
    websocket.send('u');
  }
  function servoDown(){
    websocket.send('d');
  }
  function forwardMove(){
    websocket.send('f');
  }
  function stopMove(){
    websocket.send('s');
  }
  function leftMove(){
    websocket.send('l');
  }
  function rightMove(){
    websocket.send('r');
  }
  function backwardMove(){
    websocket.send('b');
  }
</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(String(moveState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "f") == 0) {
      //ledState = !ledState;
      moveState = 5;
      notifyClients();
    }
    else if (strcmp((char*)data, "s") == 0) {
      moveState = 6;
      notifyClients();
    }
    else if (strcmp((char*)data, "l") == 0) {
      moveState = 7;
      notifyClients();
    }
    else if (strcmp((char*)data, "r") == 0) {
      moveState = 8;
      notifyClients();
    }
    else if (strcmp((char*)data, "b") == 0) {
      moveState = 9;
      notifyClients();
    }
    else if (strcmp((char*)data, "u") == 0) {
      moveState = 4;
      notifyClients();
    }
    else if (strcmp((char*)data, "d") == 0) {
      moveState = 3;
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  //Serial.println(var);
  if(var == "STATE"){
    if (moveState == 5){
      return "Forward";
    }
    else if (moveState == 6) {
      return "Stop";
    }
    else if (moveState == 7) {
      return "Left";
    }
    else if (moveState == 8) {
      return "Right";
    }
    else if (moveState == 9) {
      return "Backward";
    }
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  Serial.println(moveState);
}
