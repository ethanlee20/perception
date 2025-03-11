#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder() {}

void Encoder::begin() {
    Wire.begin();
}

float Encoder::readRawAngle() {
    int lowbyte, highbyte;
    int rawAngle;
    float degAngle;

    Wire.beginTransmission(sensorAddress);
    Wire.write(0x0D);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress, 1);

    while (Wire.available() == 0);
    lowbyte = Wire.read();

    Wire.beginTransmission(sensorAddress);
    Wire.write(0x0C);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress, 1);

    while (Wire.available() == 0);
    highbyte = Wire.read();
    highbyte = highbyte << 8;

    rawAngle = highbyte | lowbyte;
    degAngle = rawAngle * 0.087890625;

    return degAngle;
}