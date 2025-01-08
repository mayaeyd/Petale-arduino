#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>
#include "config.h"

class Sensors {
public:
    Sensors();
    void begin();
    void readAndSendData();
private:
    DHT dht;
};

#endif