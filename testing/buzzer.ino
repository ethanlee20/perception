// Test the button

#include "piezo_buzzer.hpp"


const int buzzer_pin {3};

PiezoBuzzer_Mega buzzer{buzzer_pin};


void setup() 
{   
    Serial.begin(9600);
    buzzer.initialize();
}
  

void loop() 
{
    Serial.print("Read switch input: ");
    buzzer.play(400,2000);
}