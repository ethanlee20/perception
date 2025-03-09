
#pragma once

// #include <ESP32Servo.h>
#include <Servo.h>

class ServoLidar : Servo
{
    public:
        ServoLidar(const int pin)
            : pin{pin} {}
        void initialize() {attach(pin);}
        void set_speed(int speed) 
        {
            write(speed);
        }
    private:
        const int pin;
};