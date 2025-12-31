#include <Arduino.h>
#include <esp_system.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <String.h>
#include <vector>


const char* server = "webhook.site";
const char* path = "7e748be9-eae1-43b8-8603-643052cef4fc";


std::vector<const char*> ssids = {"Wifi1", "NITDA-ICT-HUB", "WOSEMUNILAG IP EXPRESS FIBER"};
std::vector<const char*> passwds = {"pass1", "6666.2524#", "Wos1987@10unilag"};

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000;


void connectWifi() {
  Serial.begin(115200);
  delay(5000);
  for(int i = 0; i <= 2; i++){ 
    Serial.printf("Trying to connect to %s", ssids[i]);
    WiFi.begin(ssids[i], passwds[i]);
    unsigned long startAttempt = millis();
    while((WiFi.status() != WL_CONNECTED) && (millis() - startAttempt) <= 8000){
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    if(WiFi.status() == WL_CONNECTED){
      Serial.printf("Connected to %s..||..IP: %s", ssids[i], WiFi.localIP().toString().c_str());
      return;
    }
    if((WiFi.status() != WL_CONNECTED) && i==2){
      Serial.println("Couldn't connect to Wifi");
      return;
    }
  }
}

void wifiTask(void* pvParameters){
  while(true){
    if(WiFi.status() != WL_CONNECTED){
      Serial.println("Wifi Disconnected, reconnecting...");
      connectWifi();
    };
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void sendTask(void* pvParameters) {
  while(true){
    if(WiFi.status() == WL_CONNECTED){
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
    Serial.println("Server Response: ");
    Serial.println(response);
    client.stop();
  }
  else{
    Serial.println("wifi not connected, skipping data send...");
  }

  vTaskDelay(pdMS_TO_TICKS(10000));
}
}

void setup(){
  WiFi.mode(WIFI_STA);
  
  xTaskCreatePinnedToCore(wifiTask, "wifiTask", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sendTask, "sendTask", 8192, NULL, 1, NULL, 1);
}

void loop(){

}Commit on 2025-10-11T12:00:00
Commit on 2025-10-02T12:00:00
Commit on 2025-10-06T12:00:00
Commit on 2025-10-26T12:00:00
Commit on 2025-11-01T12:00:00
Commit on 2025-11-03T12:00:00
Commit on 2025-11-05T12:00:00
Commit on 2025-11-15T12:00:00
Commit on 2025-11-21T12:00:00
Commit on 2025-11-29T12:00:00
Commit on 2025-11-06T12:00:00
Commit on 2025-11-22T12:00:00
Commit on 2025-12-09T12:00:00
Commit on 2025-12-15T12:00:00
Commit on 2025-12-21T12:00:00
Commit on 2025-12-29T12:00:00
Commit on 2025-12-31T12:00:00
