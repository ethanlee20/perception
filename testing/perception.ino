#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "tof_sensor.hpp"
#include "lidar_servo.hpp"
#include "range_visualizer.hpp"

// pins
const int servo_pin {9};

// servo
const int servo_speed {80};
float servo_angle = {0}; // radians
Lidar_Servo lidar_servo {servo_pin};

// tof
ToF_Sensor tof_sensor {};

// globals
const float max_measured_radius {100}; // max visible value we give to the min(width, height) of oled
Range_Visualizer range_viz {max_measured_radius}; // just put the val here


void setup() 
{   

    //initialize environment
    Serial.begin(115200);
    Wire.begin();
    while (!Serial) {delay(1);}
    Wire.begin();

    //initialize peripherals
    lidar_servo.initialize();
    tof_sensor.initialize();
    range_viz.initialize();

    // set peripheral settings
    lidar_servo.set_speed(servo_speed);

    // start continuous ranging
    tof_sensor.startRangeContinuous();
}

void loop() 
{   
    if (tof_sensor.isRangeComplete()) {
        Serial.print("Distance in mm: ");
        Serial.println(tof_sensor.readRange());
    }

    // TOF SENSOR
    VL53L0X_RangingMeasurementData_t measurement = tof_sensor.take_measurement();
    if (measurement.RangeStatus == 0) {  
        Serial.print("Distance (mm): "); 
        Serial.println(measurement.RangeMilliMeter);
        Serial.print("Time: ");
        Serial.println(measurement.)
        range_viz.draw_dot_at(measurement.RangeMilliMeter, servo_angle);
    } 
    else {
        Serial.println("out of range ");
    }

    delay(1);
    servo_angle += 0.4;
}
