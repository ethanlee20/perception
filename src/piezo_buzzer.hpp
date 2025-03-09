
#pragma once

class PiezoBuzzer {
    public:
        static const int LEDC_TIMER = 0;
        static const int LEDC_TIMER_FREQ = 1000;
        static const int LEDC_TIMER_RES = 8;

        PiezoBuzzer(const int pin)
            : pin{pin} {}

        void initialize() {
            ledcSetup(LEDC_TIMER, LEDC_TIMER_FREQ, LEDC_TIMER_RES);
            ledcAttachPin(pin, ledc_channel);
            setVolume(duty);
        }

        void PB_ledcWriteTone(int frequency) {
            ledcWriteTone(ledc_channel, frequency);
        }
        // Function to set volume (duty cycle)
        void setVolume(int duty) {
            ledcWrite(ledc_channel, duty);  
        }


     private:
        const int pin;
        int duty = 100;
        int ledc_channel = 1;
        int ledc_frequency = 1000;
        int ledc_resolution = 8;
};

/*
class PiezoBuzzer {
    public:
        PiezoBuzzer(const int pin)
            : pin{pin} {}

        void initialize() {
            pinMode
        }
        
        void play(int freq){
            t1.play(freq);
        }

     private:
        const int pin;
        Tone t1;
};
*/
