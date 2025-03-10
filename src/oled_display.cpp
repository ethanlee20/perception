
// OLED display

//#include <SPI.h> // not necessary?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../src/oled_display.hpp"

const char* menu_mode_to_str(Menu::Mode mode) {
    if (mode == Menu::CLEAR_POINTCLOUD){
        return "   clear pointcloud"; 
    }
    else if (mode == Menu::SAVED_POINTCLOUD){
        return "   save pointcloud"; 
    }
    else if (mode == Menu::SONG_PLAYLIST){
        return "   song playlist"; 
    }
    else if (mode == Menu::STOP_GATHERING){
        return "   stop SL"; 
    }
}

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
    for (int i = 0; i < Menu::MODE_COUNT; i++) {
        if (i == mode) {
            delete_chars(0, i, 3);
            add_chars(0, i, "-> ");
            fillRect(0, i * char_height * scale, screen_width, char_height, SSD1306_INVERSE);
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
    for (int i = 0; i < Menu::MODE_COUNT; i++) {
        Menu::Mode mode = static_cast<Menu::Mode>(i);
        println(menu_mode_to_str(mode));
    }
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