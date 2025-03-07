
// OLED display


#ifndef oled_display_h
#define oled_display_h


//#include <SPI.h> // not necessary?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class OLED_Display 
{
    public:
        void initialize();
        void draw();
        void clear();
        void add_pixel(int x, int y);
        void add_text(
            String text, 
            int x, 
            int y, 
            int scale = 1
        );
        int get_screen_width(){return screen_width;}
        int get_screen_height(){return screen_height;}

    private:
        const int device_address = 0x3C;
        const int reset_pin = -1;
        const int screen_width = 128;
        const int screen_height = 64;
        Adafruit_SSD1306 display {
            screen_width, 
            screen_height, 
            &Wire, 
            reset_pin
        };
        
};

#endif