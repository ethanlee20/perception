
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

//random stuff
const float max_measured_radius {100}; // max visible value we give to the min(width, height) of oled
Range_Visualizer range_viz {max_measured_radius}; // just put the val here
unsigned long lastLEDUpdate = 0;
const unsigned long ledInterval = 2000; // 2000 milliseconds = 2 seconds
int ledState = 0;


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

    // Check if it's time to change the LED color
    unsigned long currentMillis = millis();
    if (currentMillis - lastLEDUpdate >= ledInterval) {
        lastLEDUpdate = currentMillis;
        
        // Cycle through LED states
        switch(ledState) {
        case 0:
            // Set LED to Red
            led.set_color(255, 0, 0);
            led.show();
            break;
        case 1:
            // Set LED to Green
            led.set_color(0, 255, 0);
            led.show();
            break;
        case 2:
            // Set LED to Blue
            led.set_color(0, 0, 255);
            led.show();
            break;
        case 3:
            // Clear LED (turn off)
            led.clear();
            led.show();
            break;
        }
        
        // Update the LED state to the next color
        ledState = (ledState + 1) % 4;
    }

    delay(1);
    servo_angle += 0.4;
}
