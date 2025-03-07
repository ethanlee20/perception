
// Measurement visualizer

#ifndef range_visualizer_h
#define range_visualizer_h

#include "vector_2d.hpp"
#include "oled_display.hpp"


class Range_Visualizer 
{
    public:
        Range_Visualizer(float max_measured_radius);
        void initialize();
        void clear();
        void draw_dot_at(float measured_radius, float measured_angle);

    private:
        OLED_Display display;
        float max_measured_radius;
        int max_pixel_radius;
        Quantized_Cartesian_Vector_2D convert_to_pixel_position(
            Polar_Vector_2D measured_position
        );

};


#endif

