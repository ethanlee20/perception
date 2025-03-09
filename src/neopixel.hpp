
// Neopixel class (convenience wrapper).

#pragma once // see if this works

#include <Adafruit_NeoPixel.h>


class Neopixel_LED
{
    public:
        Neopixel_LED(int led_pin)
            : led_pin {led_pin}, strip{led_count, led_pin}
        {}
        void initialize() 
        {
            strip.begin();
            strip.show();
        }
        void set_color(int red, int green, int blue)
        {
            strip.setPixelColor(led_index, red, green, blue);
        }
        void clear(){strip.clear();}
        void show(){strip.show();}
    private:
        const int led_pin;
        const int led_count{1};
        const int led_index{0};
        Adafruit_NeoPixel strip;
};