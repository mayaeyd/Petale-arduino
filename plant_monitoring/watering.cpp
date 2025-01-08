#include "watering.h"
#include <time.h>

Watering* Watering::instance = nullptr;

Watering& Watering::getInstance() {
    if (instance == nullptr) {
        instance = new Watering();
    }
    return *instance;
}

void Watering::begin() {
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    digitalWrite(PUMP_RELAY_PIN, LOW);
}

