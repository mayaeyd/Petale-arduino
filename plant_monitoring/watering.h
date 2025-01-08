#ifndef WATERING_H
#define WATERING_H

#include "config.h"

struct Schedule {
    int hour;
    int minute;
    int duration;
    bool enabled;
};

class Watering {
public:
    static Watering& getInstance();
    void begin();
    void checkSchedule();
    void waterPlants(int duration);
    void updateSchedule(int hour, int minute, int duration, bool enabled);
    Schedule getSchedule() { return wateringSchedule; }

private:
    Watering() : wateringSchedule{8, 0, 10, true} {}
    Schedule wateringSchedule;
    static Watering* instance;
};

#endif