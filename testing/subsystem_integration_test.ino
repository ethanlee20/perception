

#include "Adafruit_VL53L0X.h"
#include "tof_sensor.hpp"
#include "lidar_servo.hpp"
#include "range_visualizer.hpp"


const int servo_pin {9};
const int servo_speed {80};
float servo_angle = {0}; // radians
Lidar_Servo lidar_servo {servo_pin};

ToF_Sensor tof_sensor {};

const float max_measured_radius {100}; 
Range_Visualizer range_viz {max_measured_radius};



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
    VL53L0X_RangingMeasurementData_t measurement = tof_sensor.take_measurement();
        
    if (measurement.RangeStatus != 4) // phase failures bad
    {  
        Serial.print("Distance (mm): "); 
        Serial.println(measurement.RangeMilliMeter);
        range_viz.draw_dot_at(measurement.RangeMilliMeter, servo_angle);
    } 
    else 
    {
        Serial.println(" out of range ");
    }

    delay(1);
    servo_angle += 0.4;
}
