
#pragma once

/*
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
*/

class PiezoBuzzer_Mega {
    public:
    PiezoBuzzer_Mega(const int pin)
            : pin{pin} {}

        void initialize() {
            pinMode(pin, OUTPUT);
        }
        
        void play(int freq, int duration){
            tone(pin, freq, duration);
        }

        void stop(){
            noTone(pin);
        }

        void play_tone_nonblocking(int freq, unsigned long duration) {
            if (!playing){
                start_millis = millis();
                playing = true;

                play(freq, duration);
            }

            else{
                unsigned long current_millis = millis();

                if (current_millis - start_millis >= duration) {
                    stop();
                    playing = false;
                  }

            }
        }

        void play_song_nonblocking(int *tones, unsigned long *durations, int length) {
            // Use a static variable to remember the current tone index between calls.
            static int current_tone_index = 0;
            
            // If we've played all the tones, optionally reset for looping or simply return.
            if (current_tone_index >= length) {
                // Reset to replay the song, or simply return if you want to play it only once.
                current_tone_index = 0;  
                return;
            }
            
            // If a tone is not currently playing, start the tone.
            if (!playing) {
                start_millis = millis();
                playing = true;
                // Start playing the current tone; your play() function should initiate the tone
                tone(pin, tones[current_tone_index], durations[current_tone_index]);
            }
            else {
                // Check if the tone has been playing long enough.
                unsigned long current_millis = millis();
                if (current_millis - start_millis >= durations[current_tone_index]) {
                    // Stop the tone and mark it as finished.
                    stop();
                    playing = false;
                    // Advance to the next tone.
                    current_tone_index++;
                }
            }
        }

     private:
        const int pin;

        bool playing = false;
        unsigned long start_millis = 0;
};

