#ifndef ENCODER_H
#define ENCODER_H

#include <Wire.h>

class Encoder {
public:
    Encoder(); // Constructor
    void begin(); // Initializes I2C
    float readRawAngle(); // Reads raw angle in degrees

private:
    const int sensorAddress = 0x36;
};

#endif // ENCODER_H