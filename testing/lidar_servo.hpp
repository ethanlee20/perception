
#pragma once

#include <Servo.h>


class Lidar_Servo
{
    public:
        Lidar_Servo(int pin)
            : pin{pin} {}
        void initialize() {our_servo.attach(pin);}
        void set_speed(int speed) 
        {
            our_servo.write(speed);
        }
    private:
        Servo our_servo;
        const int pin;
};