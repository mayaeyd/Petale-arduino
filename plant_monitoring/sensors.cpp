#include "sensors.h"
#include "websocket_handler.h"
#include <ArduinoJson.h>

Sensors::Sensors() : dht(DHTPIN, DHTTYPE) {}

void Sensors::begin() {
    delay(1000);
    dht.begin();
    delay(2000);
}

void Sensors::readAndSendData() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int soilMoisture = map(analogRead(SOIL_MOISTURE_PIN), 0, 1023, 100, 0);
    
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);

    if (!isnan(temperature) && !isnan(humidity)) {
        DynamicJsonDocument doc(200);
        doc["type"] = "sensor_data";
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;
        doc["soil_moisture"] = soilMoisture;
        
        String output;
        serializeJson(doc, output);
        WebSocketHandler::getInstance().sendMessage(output);
    } else {
        Serial.println("Failed to read from DHT sensor!");
    }
}