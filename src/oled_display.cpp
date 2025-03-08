
// OLED display

//#include <SPI.h> // not necessary?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled_display.hpp"


void OLED_Display::initialize()
{
    bool success = display.begin(
        SSD1306_SWITCHCAPVCC, 
        device_address
    );
    if (!success) 
    {
        Serial.println(
            F("OLED display initialization failed :(")
        );
        for(;;); // stop (loop forever)
    }

    display.cp437(true); // set font

    display.display(); // adafruit logo screen
    delay(2000);
    display.clearDisplay();
    display.display();
}


void OLED_Display::draw()
{
    display.display();
}


void OLED_Display::clear()
{
    display.clearDisplay();
}


void OLED_Display::add_pixel(int x, int y)
{
    display.drawPixel(x, y, SSD1306_WHITE);
}


void OLED_Display::add_text(
    String text, int x, int y, int scale
)
{
    display.setTextSize(scale);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(text);
}
