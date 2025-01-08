#include "config.template.h"
#include "sensors.h"
#include "websocket_handler.h"
#include "watering.h"

Sensors sensors;

void setup() {
    Serial.begin(9600);
    
    sensors.begin();
    Watering::getInstance().begin();

    WebSocketHandler::getInstance().begin();
}

