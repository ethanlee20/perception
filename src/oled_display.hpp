
// OLED display


#ifndef oled_display_h
#define oled_display_h


//#include <SPI.h> // not necessary?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED_Display : public Adafruit_SSD1306 {
    public:

        OLED_Display() : Adafruit_SSD1306(
            screen_width,
            screen_height,
            &Wire,
            reset_pin
        ) {}

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

        void display_menu(const int row = 0);

    private:
        static constexpr int device_address = 0x3C;
        static constexpr int reset_pin = -1;
        static constexpr int screen_width = 128;
        static constexpr int screen_height = 64;
        static constexpr int char_width = 6;
        static constexpr int char_height = 8;
        int scale = 1;

        void default_display_menu();
        void delete_chars(int row_index, int col_index, int range);
        void add_chars(int row_index, int col_index, const char *letters);
};

#endif