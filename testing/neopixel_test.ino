// Test the neopixel


#include "neopixel.hpp"


const int led_pin {6};

Neopixel_LED led{led_pin};


void setup() 
{
    // Red
    led.set_color(255, 0, 0);
    led.show();
    delay(5000);

    // Green
    led.set_color(0, 255, 0);
    led.show();
    delay(5000);

    // Blue
    led.set_color(0, 0, 255);
    led.show();
    delay(5000);

    // Clear?
    led.clear();
    delay(5000);
}
  

void loop() 
{
    // put your main code here, to run repeatedly:
  
}