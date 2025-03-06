
// Measurement visualizer

#include "vector_2d.hpp"
#include "oled_display.hpp"


class Range_Visualizer 
{
    public:
        Range_Visualizer(double max_measured_radius);
        void clear();
        void draw_position();

    private:
        OLED_Display oled_display {};
        const int max_pixel_radius = 
};

