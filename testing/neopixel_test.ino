// Test the neopixel


#include "neopixel.hpp"


const int led_pin {6};

Neopixel_LED led{led_pin};


void setup() 
{   
    led.initialize();
    
}
  

void loop() 
{
    // Red
    led.set_color(255, 0, 0);
    led.show();
    delay(2000);

    // Green
    led.set_color(0, 255, 0);
    led.show();
    delay(2000);

    // Blue
    led.set_color(0, 0, 255);
    led.show();
    delay(2000);

    // Clear?
    led.clear();
    led.show();
    delay(2000);
  
}