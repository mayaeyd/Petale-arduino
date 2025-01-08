#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>

// Pin Definitions
#define DHTPIN D2
#define SOIL_MOISTURE_PIN A0
#define PUMP_RELAY_PIN D1
#define DHTTYPE DHT11

// Network settings
#define WEBSOCKET_RECONNECT_INTERVAL 5000
#define MAX_RETRIES 3

// Network credentials - REPLACE THESE
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// WebSocket server settings - REPLACE THESE
const char* wsHost = "YOUR_WEBSOCKET_HOST";
const int wsPort = YOUR_WEBSOCKET_PORT;

#endif