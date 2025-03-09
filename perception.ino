
#include <Wire.h>

#include "src/neopixel.hpp"
#include "src/range_visualizer.hpp"
#include "src/servo_lidar.hpp"
#include "src/tof_sensor.hpp"


// #include "src/piezo_buzzer.hpp"

const int servo_pin {5};
const int piezo_buzzer_pin {3};
const int led_pin {6};

const int servo_speed {0};
float servo_angle = {0}; // radians

Neopixel_LED led{led_pin};
// PiezoBuzzer piezo_buzzer {piezo_buzzer_pin};
ServoLidar servo_lidar {servo_pin};
ToF_Sensor tof_sensor {}; //i2c

const float max_measured_radius {100}; // max visible value we give to the min(width, height) of oled
Range_Visualizer range_viz {max_measured_radius}; // just put the val here


void setup() 
{   
    Serial.begin(9600);
    while (!Serial) {delay(1); Serial.println("waiting for Serial");}
    Serial.println("Starting");
    Wire.begin();
    Serial.println("Wire began");

    Serial.println("initializing");
    servo_lidar.initialize(); Serial.println("Servo done");
    tof_sensor.initialize(); Serial.println("TOF done");
    range_viz.initialize(); Serial.println("Range visualizer done");
    led.initialize(); Serial.println("Neopixel done");
    // piezo_buzzer.initialize();Serial.println("Piezo buzzer done");
    
    servo_lidar.set_speed(servo_speed);
    tof_sensor.startRangeContinuous();

    Serial.println("finished setup");
}

void loop() 
{   

    if (tof_sensor.isRangeComplete()) {
        Serial.print("Distance (mm): "); Serial.println(tof_sensor.readRange());
    }

    /*
    // TOF SENSOR
    VL53L0X_RangingMeasurementData_t measurement; = tof_sensor.take_measurement();
    if (measurement.RangeStatus == 0) {  
        Serial.print("Distance (mm): "); 
        Serial.println(measurement.RangeMilliMeter);
        Serial.print("Time: ");
        Serial.println(measurement.TimeStamp);
        range_viz.draw_dot_at(measurement.RangeMilliMeter, servo_angle);
    } 
    else if (measurement.RangeStatus == 2){
        Serial.println("Error 2: Signal Fail: The signal check has failed, possibly due to the absence of a target or a failed Range Ignore threshold check.");
    }
    else if (measurement.RangeStatus == 3){
        Serial.println("target too close");
    }
    else if (measurement.RangeStatus == 4){
        Serial.println("Error 4: Phase Fail: The phase check has failed, suggesting issues with the sensor's timing or signal processing.");
    }
    else if (measurement.RangeStatus == 5){
        Serial.println("Error 5: Hardware Fail: A hardware error has occurred during the ranging process.");
    }
    else {
        Serial.println("something went wrong");
    }
    */
   
    //PIEZO BUZZER

    //Serial.println(200);
    //piezo_buzzer.PB_ledcWriteTone(200);
    //delay(500);
    //Serial.println(400);
    //piezo_buzzer.PB_ledcWriteTone(300);
    //delay(500);
    //Serial.println(500);
    //piezo_buzzer.PB_ledcWriteTone(500);
    //delay(500);

    // Red
    led.set_color(255, 0, 0);
    led.show();
    // delay(2000);

    // Green
    led.set_color(0, 255, 0);
    led.show();
    // delay(2000);

    // Blue
    led.set_color(0, 0, 255);
    led.show();
    // delay(2000);

    // Clear?
    led.clear();
    led.show();
    // delay(2000);

    delay(1);
    servo_angle += 0.4;
}
