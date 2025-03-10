#pragma once

class Mic {
    public:
        Mic(const int pin)
            : pin{pin} {}
          
        double sample() {
            static bool listening = false;
            static unsigned long start_time = 0;
            static unsigned signal_min = _signal_min;
            static unsigned signal_max = _signal_max;

            if (!listening){
                start_time = millis();
                listening = true;
                signal_min = _signal_min;
                signal_max = _signal_max;
            }
            
            unsigned int sample;
            // collect data for 50 mS
            if (millis() - start_time < sample_window){
                sample = analogRead(pin);
                if (sample < 1024) { // toss out spurious readings
                    if (sample > signal_max){
                        signal_max = sample;  // save just the max levels
                    } else if (sample < signal_min){
                        signal_min = sample;  // save just the min levels
                    }
                }
                return -1;
            }
            else{
                int peakToPeak = signal_max - signal_min;  // max - min = peak-peak amplitude
                double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
                listening = false;
                return volts;
            }   
        }


     private:
        const int pin = 0;
        const unsigned _signal_min = 1024;
        const unsigned _signal_max = 0;
        int sample_window = 50; // Sample window width in mS (50 mS = 20Hz)
};