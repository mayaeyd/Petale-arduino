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

    
}