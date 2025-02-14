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

void Watering::checkSchedule() {
    if (!wateringSchedule.enabled) return;
    
    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&now);
    
    if (timeinfo->tm_hour == wateringSchedule.hour && 
        timeinfo->tm_min == wateringSchedule.minute && 
        timeinfo->tm_sec == 0) {
        waterPlants(wateringSchedule.duration);
    }
}

void Watering::waterPlants(int duration) {
    digitalWrite(PUMP_RELAY_PIN, HIGH);
    delay(duration * 1000);
    digitalWrite(PUMP_RELAY_PIN, LOW);
}

void Watering::updateSchedule(int hour, int minute, int duration, bool enabled) {
    wateringSchedule.hour = hour;
    wateringSchedule.minute = minute;
    wateringSchedule.duration = duration;
    wateringSchedule.enabled = enabled;
}