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

void WebSocketHandler::begin() {
    webSocket.begin(wsHost, wsPort, "/ws");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
}

void WebSocketHandler::loop() {
    webSocket.loop();
    reconnectWebSocket();
}

void WebSocketHandler::sendMessage(const String& message) {
    webSocket.sendTXT(message);
}

void WebSocketHandler::webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    getInstance().webSocketConnected = (type == WStype_CONNECTED);
    
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("Disconnected from WebSocket server");
            break;
        case WStype_CONNECTED:
            Serial.println("Connected to WebSocket server");
            break;
        case WStype_TEXT:
            getInstance().handleWebSocketMessage(payload, length);
            break;
        case WStype_ERROR:
            Serial.println("WebSocket Error");
            getInstance().webSocketConnected = false;
            break;
    }
}
