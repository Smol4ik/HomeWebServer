#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
 
#define PinLed 2
const char* ssid = "ssid";
const char* password = "password";
const char* server = "http://192.168.0.103:5555/get/data/led";

unsigned long lastTime = 0;
unsigned long timerDelay = 2000;

String sensorReadings;

void setup(){
  pinMode(PinLed, OUTPUT);
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void loop(){
if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
              
      sensorReadings = httpGETRequest(server);
      JSONVar myObject = JSON.parse(sensorReadings);
      String ledDataValue = myObject["state"];
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      if(ledDataValue == "on") {
        digitalWrite(PinLed, HIGH);
      }
      else {
        digitalWrite(PinLed, LOW);
      }
      Serial.print("JSON object = ");
      Serial.println(myObject["state"]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
String httpGETRequest(const char* server) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, server);
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}