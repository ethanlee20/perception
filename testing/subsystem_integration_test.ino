

#include "Adafruit_VL53L0X.h"
#include "../src/tof_sensor.hpp"
#include "../src/lidar_servo.hpp"
#include "../src/range_visualizer.hpp"


const int servo_pin {9};
const int servo_speed {80};
float servo_angle = {0}; // radians
Lidar_Servo lidar_servo {servo_pin};

ToF_Sensor tof_sensor {};

const float max_measured_radius {100}; // max visible value we give to the min(width, height) of oled
Range_Visualizer range_viz {max_measured_radius}; // just put the val here



void setup() 
{
    Serial.begin(115200);
    while (!Serial) {delay(1);}

    lidar_servo.initialize();
    tof_sensor.initialize();
    range_viz.initialize();

    lidar_servo.set_speed(servo_speed);
}

void loop() 
{   

    // TOF SENSOR
    VL53L0X_RangingMeasurementData_t measurement = tof_sensor.take_measurement();
    if (measurement.RangeStatus == 0) {  
        Serial.print("Distance (mm): "); 
        Serial.println(measurement.RangeMilliMeter);
        Serial.print("Time: ");
        Serial.println(measurement.TimeStamp);
        range_viz.draw_dot_at(measurement.RangeMilliMeter, servo_angle);
    } 
    else {
        Serial.println("out of range ");
    }

    delay(1);
    servo_angle += 0.4;
}
