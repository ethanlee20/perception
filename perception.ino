
#include <Wire.h>

#include "src/neopixel.hpp"
#include "src/range_visualizer.hpp"
#include "src/servo_lidar.hpp"
#include "src/tof_sensor.hpp"
#include "src/button.hpp"
#include "src/oled_display.hpp"
#include "src/piezo_buzzer.hpp"
#include "src/mic.hpp"

const int piezo_buzzer_pin {3};
const int servo_pin {5};
const int led_pin {6};
const int button_center_pin {7};
const int button_down_pin {8};
const int button_up_pin {9};
const int mic_pin {0};

//random stuff
const int servo_speed {0};
float servo_angle = {0}; // radians
const float max_measured_radius {100}; // max visible value we give to the min(width, height) of oled
unsigned long lastLEDUpdate = 0;
const unsigned long ledInterval = 2000; // 2000 milliseconds = 2 seconds
int ledState = 0;
unsigned long D3 = 146.8;
unsigned long D3_sharp = 155.6;
unsigned long F3 = 174.6;
unsigned long F3_sharp = 185.0;
unsigned long G3 = 196.0;
unsigned long G3_sharp = 207.7;
unsigned long C4 = 261.6; //middle C
unsigned long C4_sharp = 277.2;
unsigned long D4 = 293.7;
unsigned long D4_sharp = 311.1;
unsigned long F4 = 349.2;
unsigned long F4_sharp = 370.0;

int quarter_note = 500;
int eight_note = quarter_note / 2;
int songTones[] = {D4_sharp, F4, C4_sharp, D4_sharp, F4_sharp, F4, C4_sharp, D4_sharp};
unsigned long songDurations[] = {quarter_note, eight_note, quarter_note, quarter_note * 5, quarter_note, eight_note, quarter_note, quarter_note * 5};
int songLength = sizeof(songTones) / sizeof(songTones[0]);


PiezoBuzzer_Mega piezo_buzzer {piezo_buzzer_pin};
Button button_center{button_center_pin};
Button button_down{button_down_pin};
Button button_up{button_up_pin};
ServoLidar servo_lidar {servo_pin};
Neopixel_LED led{led_pin};
ToF_Sensor tof_sensor {}; //i2c
OLED_Display display {};
Range_Visualizer range_viz {&display, max_measured_radius}; // just put the val here
Mic mic(0);


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
    led.initialize(); Serial.println("Neopixel done");
    piezo_buzzer.initialize();Serial.println("Piezo buzzer done");
    button_center.initialize(); Serial.println("Button center done");
    button_down.initialize(); Serial.println("Button down done");
    button_up.initialize(); Serial.println("Button up done");
    display.initialize(); Serial.println("display done");
    range_viz.initialize(); Serial.println("Range visualizer done");
    
    servo_lidar.set_speed(servo_speed);
    tof_sensor.startRangeContinuous();

    Serial.println("finished setup");
}

void loop() 
{   

    if (display.display_mode == Display::RANGEVIZ && tof_sensor.isRangeComplete()) {
        uint16_t distance = tof_sensor.readRange();
        Serial.print("Distance (mm): "); Serial.println(distance);
        range_viz.draw_dot_at(distance, servo_angle);
    }
    /*
    VL53L0X_RangingMeasurementData_t measurement; = tof_sensor.take_measurement();
     if (measurement.RangeStatus == 0) {  
         Serial.print("Distance (mm): "); 
         Serial.println(measurement.RangeMilliMeter);
         Serial.print("Time: ");
         Serial.println(measurement.TimeStamp);
         range_viz.draw_dot_at(measurement.RangeMilliMeter, servo_angle);
     } 
    */

    //PIEZO BUZZER
    /*
    Serial.println(200);
    piezo_buzzer.PB_ledcWriteTone(200);
    delay(500);
    Serial.println(400);
    piezo_buzzer.PB_ledcWriteTone(300);
    delay(500);
    Serial.println(500);
    piezo_buzzer.PB_ledcWriteTone(500);
    delay(500);
    */
    piezo_buzzer.play_song_nonblocking(songTones, songDurations, songLength);


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
    
    
    /*
    // MIC
    double sample = mic.sample();
    if (sample != -1 && sample > 0.1){
      Serial.print("Audio level: ");
      Serial.println(sample);
      led.set_color(155, 0, 255);
      led.show();
    }
    else if (sample !=1 && sample < 0.1){
      led.set_color(40, 20, 70);
      led.show();
    }
    */

    if (button_center.read_toggle() && button_center.read()){
      Serial.println("Center button read");
        if (display.display_mode == Display::RANGEVIZ){
            Serial.println("switch from range mode to menu");
            display.display_menu();
            led.set_color(0, 0, 255);
            display.display_mode = Display::MENU;
        }
        else { // we're in menu mode. for now just clear
            Serial.println("switch from menu mode to range");
            display.clearDisplay();
            display.display_mode = Display::RANGEVIZ;
            // select menu mode
        }
    }
    else if (button_down.read_toggle() && button_down.read() && display.display_mode == Display::MENU){
        display.menu_mode = ((display.menu_mode + 1) % Menu::MODE_COUNT);
        display.display_menu(display.menu_mode);
    }
    else if (button_up.read_toggle() && button_up.read() && display.display_mode == Display::MENU){
        display.menu_mode = ((display.menu_mode + Menu::MODE_COUNT - 1) % Menu::MODE_COUNT);
        display.display_menu(display.menu_mode);
    }

    delay(1);
    servo_angle += 0.4;
}
