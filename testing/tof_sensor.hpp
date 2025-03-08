
#pragma once

#include "Adafruit_VL53L0X.h"


class ToF_Sensor 
{
    public:
        void initialize()
        {
            bool success {sensor.begin()};

            while (!success) {
                Serial.println(F("ToF sensor init failed. Tryin again("));
                delay(100);
                success = sensor.begin();
            }            
        }
        VL53L0X_RangingMeasurementData_t take_measurement()
        {
            VL53L0X_RangingMeasurementData_t measurement {};
            sensor.rangingTest(&measurement, false); // debug off
            return measurement;
        }
    private:
        Adafruit_VL53L0X sensor {};
};