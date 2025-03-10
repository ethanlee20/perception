

// Arduino file for testing the display.

#include "oled_display.hpp"


OLED_Display disp;

void setup() 
{
    disp.initialize(); // should show Adafruit logo.
    
    // should display "Hello, World!".
    disp.add_text(String{"Hello, World!"}, 0, 0);
    disp.draw(); 
    delay(5000);

    // should clear display.
    disp.clear(); 
    
    // should light up every pixel in order
    for (int row = 0; row < disp.get_screen_height(); row++)
    {
        for (int col = 0; col < disp.get_screen_width(); col++)
        {
            disp.add_pixel(col, row);
            disp.draw();
        }
    }
    delay(1000);

    disp.clear();

    disp.display_menu(1);
}
  
void loop() 
{
    
}