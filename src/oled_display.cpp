
// OLED display

//#include <SPI.h> // not necessary?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled_display.hpp"


void OLED_Display::initialize() {
    bool success = begin(SSD1306_SWITCHCAPVCC, device_address);

    while (!success) {
        Serial.println(F("Display sensor init failed. Tryin again("));
        delay(100);
        success = begin();
    }

    cp437(true); // set font

    display(); // adafruit logo screen
    delay(2000);
    clearDisplay();
    display();
}


void OLED_Display::draw()
{
    display();
}


void OLED_Display::clear()
{
    clearDisplay();
}


void OLED_Display::add_pixel(int x, int y)
{
    drawPixel(x, y, SSD1306_WHITE);
}


void OLED_Display::add_text(
    String text, int x, int y, int scale
)
{
    setTextSize(scale);
    setTextColor(SSD1306_WHITE);
    setCursor(x, y);
    println(text);
}
