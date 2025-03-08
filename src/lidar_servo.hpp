
#pragma once

#include <ESP32Servo.h>


class Lidar_Servo : Servo
{
    public:
        Lidar_Servo(const int pin)
            : pin{pin} {}
        void initialize() {attach(pin);}
        void set_speed(int speed) 
        {
            write(speed);
        }
    private:
        const int pin;
};