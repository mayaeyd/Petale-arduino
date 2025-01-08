#include "websocket_handler.h"
#include "watering.h"
#include <ArduinoJson.h>

WebSocketHandler* WebSocketHandler::instance = nullptr;

WebSocketHandler& WebSocketHandler::getInstance() {
    if (instance == nullptr) {
        instance = new WebSocketHandler();
    }
    return *instance;
}

