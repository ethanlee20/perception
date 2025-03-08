
#pragma once

#include "Adafruit_VL53L0X.h"


class ToF_Sensor : public Adafruit_VL53L0X {
    public:
        void initialize() {
            bool success {begin()};

            while (!success) {
                Serial.println(F("ToF sensor init failed. Tryin again("));
                delay(100);
                success = begin();
            }
        }

        VL53L0X_RangingMeasurementData_t take_measurement() {
            VL53L0X_RangingMeasurementData_t measurement {};
            rangingTest(&measurement, false); // debug off
            return measurement;
        }            
};