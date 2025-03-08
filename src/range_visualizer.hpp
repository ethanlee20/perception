
// Measurement visualizer

#ifndef range_visualizer_h
#define range_visualizer_h

#include "vector_2d.hpp"
#include "oled_display.hpp"


class Range_Visualizer 
{
    public:
        Range_Visualizer(const float max_measured_radius);
        void initialize();
        void clear();
        void draw_dot_at(float measured_radius, float measured_angle);

    private:
        OLED_Display display;
        const float max_measured_radius; // change name
        const int max_pixel_radius; // change name
        Quantized_Cartesian_Vector_2D convert_to_pixel_position(
            Polar_Vector_2D measured_position
        );

};


#endif

