
#pragma once

#include "Adafruit_VL53L0X.h"


class ToF_Sensor 
{
    public:
        void initialize()
        {
            bool success {sensor.begin()};
            if (!success)
            {
                Serial.println(F("ToF sensor init failed :("));
                while(1); // stall out
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