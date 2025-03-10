#pragma once

class Button
{
    public:
        Button(const int pin)
            : pin{pin} {}

        void initialize(){
            pinMode(pin, INPUT);    // sets the digital pin as input to read switch
        }

        bool read(){
            return digitalRead(pin);
        }

        bool read_toggle(){
            bool current_state = read();
            if (current_state != last_button_state) {
                last_debounce_time = millis();
            }

            if ((millis() - last_button_state) > debounce_delay) {
                if (last_button_state == LOW && current_state == HIGH){
                    last_button_state = current_state;
                    return true;
                }
            }
            last_button_state = current_state;
            return false;
        }

    private:
        const int pin;
        unsigned long last_debounce_time = millis();
        const unsigned long debounce_delay = 50;
        bool last_button_state = false;  // current state of the button

};