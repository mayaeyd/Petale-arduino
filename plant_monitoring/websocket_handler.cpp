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


