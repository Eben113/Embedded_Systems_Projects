#include <Arduino.h>
#include <esp_system.h>
#include <WiFiClientSecure.h>
#include <Wifi.h>
#include <ArduinoJson.h>
#include <String.h>


const char* server = "webhook.site";
const char* path = "7e748be9-eae1-43b8-8603-643052cef4fc";

const char* ssid = "WOSEMUNILAG IP EXPRESS FIBER";
const char* passwd = "Wos1987@10unilag";

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000;


void setup() {
  Serial.begin(115200);
  Serial.print("started");
  WiFi.begin(ssid, passwd);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print("Connecting to wifi...\n");
  }
  Serial.print("\nWifi Connected");
}

void loop() {
  if((millis() - lastSendTime) >= sendInterval){
    lastSendTime = millis();

    WiFiClientSecure client;
    client.setInsecure();
    if(!client.connect(server, 443)){
      Serial.println("Server connection failed");
      return;
    }

    int temp = 25;
    int humidity = 60;

    String jsonData = "{""\"temperature\":" + String(temp) + ",""\"humidity\":" + String(humidity) + "}";

    client.println("POST" + String(path) + "HTTP/1.1");
    client.println("Host" + String(server));
    client.println("Content-Type: application/json");
    client.println(jsonData.length());
    client.println("Connection close");
    client.println();
    client.println(jsonData);
                                                   
    String response = "";
    while(client.connected() || client.available()){
      if(client.available()){
        response += client.readStringUntil('\n');
      }
    }
    client.stop();
  }
}

Commit on 2025-10-03T12:00:00
Commit on 2025-10-07T12:00:00
Commit on 2025-10-13T12:00:00
Commit on 2025-10-17T12:00:00
Commit on 2025-10-06T12:00:00
Commit on 2025-11-19T12:00:00
Commit on 2025-11-30T12:00:00
Commit on 2025-11-14T12:00:00
Commit on 2026-01-04T12:00:00
