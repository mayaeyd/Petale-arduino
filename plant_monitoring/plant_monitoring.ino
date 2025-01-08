#include "config.h"
#include "sensors.h"
#include "websocket_handler.h"
#include "watering.h"

Sensors sensors;

void setup() {
    Serial.begin(9600);
    
    sensors.begin();
    Watering::getInstance().begin();
    
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    WebSocketHandler::getInstance().begin();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi disconnected. Reconnecting...");
        WiFi.begin(ssid, password);
        delay(5000);
        return;
    }

    WebSocketHandler::getInstance().loop();
    
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 2500) {
        sensors.readAndSendData();
        lastUpdate = millis();
    }
    
    Watering::getInstance().checkSchedule();
    delay(200);
}