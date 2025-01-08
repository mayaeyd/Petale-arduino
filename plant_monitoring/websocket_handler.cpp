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

void WebSocketHandler::handleWebSocketMessage(uint8_t * payload, size_t length) {
    DynamicJsonDocument doc(200);
    DeserializationError error = deserializeJson(doc, payload);
    
    if (!error) {
        const char* type = doc["type"];
        
        if (strcmp(type, "water_now") == 0) {
            int duration = doc["duration"] | 10;
            Watering::getInstance().waterPlants(duration);
        }
        else if (strcmp(type, "update_schedule") == 0) {
            Watering::getInstance().updateSchedule(
                doc["hour"] | Watering::getInstance().getSchedule().hour,
                doc["minute"] | Watering::getInstance().getSchedule().minute,
                doc["duration"] | Watering::getInstance().getSchedule().duration,
                doc["enabled"] | Watering::getInstance().getSchedule().enabled
            );
        }
    }
}

void WebSocketHandler::reconnectWebSocket() {
    if (!webSocketConnected && (millis() - lastWebSocketReconnectAttempt > WEBSOCKET_RECONNECT_INTERVAL)) {
        Serial.println("Attempting WebSocket reconnection...");
        webSocket.begin(wsHost, wsPort, "/ws");
        lastWebSocketReconnectAttempt = millis();
    }
}
