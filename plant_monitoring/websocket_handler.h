#ifndef WEBSOCKET_HANDLER_H
#define WEBSOCKET_HANDLER_H

#include <WebSocketsClient.h>
#include "config.h"

class WebSocketHandler {
public:
    static WebSocketHandler& getInstance();
    void begin();
    void loop();
    void sendMessage(const String& message);
    bool isConnected() { return webSocketConnected; }

private:
    WebSocketHandler() {}
    static void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
    void handleWebSocketMessage(uint8_t * payload, size_t length);
    void reconnectWebSocket();

    static WebSocketHandler* instance;
    WebSocketsClient webSocket;
    bool webSocketConnected = false;
    unsigned long lastWebSocketReconnectAttempt = 0;
};

#endif