
// OLED display

//#include <SPI.h> // not necessary?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../src/oled_display.hpp"


void OLED_Display::initialize() {
    bool success = begin(SSD1306_SWITCHCAPVCC, device_address);

    while (!success) {
        Serial.println(F("Display sensor init failed. Tryin again("));
        delay(100);
        success = begin();
    }

    cp437(true); // set font
    setTextSize(1);      // Normal 1:1 pixel scale
    setTextColor(SSD1306_WHITE); // Draw white text
    setCursor(0, 0);     // Start at top-left corner

    display(); // adafruit logo screen
    delay(500);
    clearDisplay();
    display();
}


void OLED_Display::draw(){
    display();
}


void OLED_Display::clear(){
    clearDisplay();
}


void OLED_Display::add_pixel(int x, int y){
    drawPixel(x, y, SSD1306_WHITE);
}


void OLED_Display::add_text(
    String text, int x, int y, int scale
){
    setTextSize(scale);
    setTextColor(SSD1306_WHITE);
    setCursor(x, y);
    println(text);
}

void OLED_Display::display_menu(const int mode) {
    // Clear the buffer
    clearDisplay();
    default_display_menu();
    setCursor(0, 0);
    display();
    
    // Display menu options with an arrow for the selected one
    for (int i = 0; i < 3; i++) {
        if (i == mode) {
            delete_chars(0, i, 3);
            add_chars(0, i, "-> ");
            fillRect(0, i, screen_width, char_height, SSD1306_INVERSE);
        }
    }
    
    // Write the buffer to the display
    display();
  }

void OLED_Display::default_display_menu() {
    // Clear the buffer
    clearDisplay();
    // Display the header
    setCursor(0, 0);
    println("Select Option:");

    println("   Save pointcloud"); // Padding for unselected options
    println("   Clear pointcloud");
    println("   Song Playlist");
    println("   Exit");
}

void OLED_Display::delete_chars(int x, int y, int range){
    int xPos = x * char_width * scale; // compute x position of letter
    int yPos = y * char_height * scale; // compute y position of letter

    // Clear the area of the letter by drawing a black filled rectangle
    fillRect(xPos, yPos, char_width * scale * range, char_height * scale, SSD1306_BLACK);
}

void OLED_Display::add_chars(int x, int y, const char *letters){
    int xPos = x * char_width * scale; // compute x position of letter
    int yPos = y * char_height * scale; // compute y position of letter
    setCursor(xPos, yPos);
    print(letters);
}