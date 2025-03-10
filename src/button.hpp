#pragma once

class Button
{
    public:
        Button(const int pin)
            : pin{pin} {}

        void initialize(){
            pinMode(pin, INPUT);    // sets the digital pin as input to read switch
        }

        int read(){
            return digitalRead(pin);
        }
    private:
        const int pin;
};