
#include "Adafruit_VL53L0X.h"
#include "src/tof_sensor.hpp"
#include "src/servo_lidar.hpp"
#include "src/range_visualizer.hpp"
#include "src/piezo_buzzer.hpp"

const int servo_pin {5};
const int piezo_buzzer_pin {3};
const int servo_speed {0};
float servo_angle = {0}; // radians
ServoLidar servo_lidar {servo_pin};
PiezoBuzzer piezo_buzzer {piezo_buzzer_pin};

ToF_Sensor tof_sensor {};

const float max_measured_radius {100}; // max visible value we give to the min(width, height) of oled
Range_Visualizer range_viz {max_measured_radius}; // just put the val here


void setup() 
{
    Serial.begin(115200);
    while (!Serial) {delay(1);}

    servo_lidar.initialize();
    tof_sensor.initialize();
    range_viz.initialize();
    piezo_buzzer.initialize();

    servo_lidar.set_speed(servo_speed);
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

    //PIEZO BUZZER

    Serial.println(200);
    piezo_buzzer.PB_ledcWriteTone(200);
    delay(500);
    Serial.println(400);
    piezo_buzzer.PB_ledcWriteTone(300);
    delay(500);
    Serial.println(500);
    piezo_buzzer.PB_ledcWriteTone(500);
    delay(500);

    delay(1);
    servo_angle += 0.4;
}
