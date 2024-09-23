#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 2  
#define DHTTYPE DHT11

const char* ssid = "ssid";
const char* password = "password";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.0.103:5555/post/temperature/humidity";
float previousTemperature1;
bool temperature1State = true;
float previousTemperature2;
bool temperature2State = false;
float previousTemperature3;
bool temperature3State = false;
float previousTemperature4;
bool temperature4State = false;

float arrTemp[4] = {previousTemperature1, previousTemperature2, previousTemperature3, previousTemperature4};
float previousHumidity;

   

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

void setup() {
  Serial.begin(9600);
  dht.begin();

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

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float compareTempValue = abs(previousTemperature4 - previousTemperature1);
  float compareHumValue = abs(humidity - previousHumidity);
  if((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      if(compareTempValue > 0.5 || compareHumValue > 8) {
        http.begin(client, serverName);
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.POST("{\"temperature\":\""+String(temperature)+"\",\"humidity\":\""+String(humidity)+"\"}");
        if (httpResponseCode == 201) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
        }
        else {
          Serial.print("Error Response code: ");
          Serial.println(httpResponseCode);
        }
      }
      else {
        Serial.println("The temperature or humidity has hardly changed");
      }

      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
      Serial.print(F("Humidity: "));
      Serial.print(humidity);
      Serial.print(F("%  Temperature: "));
      Serial.print(temperature);
      Serial.println(F("°C "));

      if(temperature1State) {
        previousTemperature1 = temperature;
        temperature1State = false;
        temperature2State = true;
      }
      else if(temperature2State) {
        previousTemperature2 = temperature;
        temperature2State = false;
        temperature3State = true;
      }
      else if(temperature3State) {
        previousTemperature3 = temperature;
        temperature3State = false;
        temperature4State = true;
      }
      else if(temperature4State) {
        previousTemperature4 = temperature;
        temperature1State = true;
        temperature4State = false;
      }
      arrTemp[0] = previousTemperature1;
      arrTemp[1] = previousTemperature2;
      arrTemp[2] = previousTemperature3;
      arrTemp[3] = previousTemperature4;

      previousHumidity = humidity;
      for (int i = 0; i < 4; i++) {
        Serial.print(arrTemp[i]);
        Serial.print((i < 3) ? ", " : ""); 
      }
      Serial.println();
      lastTime = millis();
    }
  }