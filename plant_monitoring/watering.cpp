#include "watering.h"
#include <time.h>

Watering* Watering::instance = nullptr;

Watering& Watering::getInstance() {
    if (instance == nullptr) {
        instance = new Watering();
    }
    return *instance;
}

