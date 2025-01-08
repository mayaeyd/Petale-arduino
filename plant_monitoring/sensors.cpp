#include "sensors.h"
#include "websocket_handler.h"
#include <ArduinoJson.h>

Sensors::Sensors() : dht(DHTPIN, DHTTYPE) {}

void Sensors::begin() {
    delay(1000);
    dht.begin();
    delay(2000);
}

