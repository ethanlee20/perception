// Test the button

#include "button.hpp"


const int button_pin {13};

Button button{button_pin};


void setup() 
{   
    Serial.begin(9600);
    button.initialize();
}
  

void loop() 
{
    Serial.print("Read switch input: ");
    Serial.println(button.read());
}