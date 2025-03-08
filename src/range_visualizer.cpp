


#include "vector_2d.hpp"
#include "range_visualizer.hpp"
// #include "oled_display.hpp"


Range_Visualizer::Range_Visualizer(const float max_measured_radius) 
    : display(),
      max_measured_radius{ max_measured_radius },
      max_pixel_radius{ (display.get_screen_height() / 2) - 1 } 
{}

void Range_Visualizer::initialize()
{
    display.initialize();
}


void Range_Visualizer::clear()
{
    display.clear();
    display.draw();
}


void Range_Visualizer::draw_dot_at(float measured_radius, float measured_angle)
{
    Polar_Vector_2D measured_position {measured_radius, measured_angle};
    Quantized_Cartesian_Vector_2D pixel_position = convert_to_pixel_position(
        measured_position
    );
    display.add_pixel( // origin at middle of screen, +x is up, +y is right
        pixel_position.get_x() + display.get_screen_width()/2, 
        -pixel_position.get_y() + display.get_screen_height()/2
    );
    display.draw();
}


Quantized_Cartesian_Vector_2D Range_Visualizer::convert_to_pixel_position(
    Polar_Vector_2D measured_position
)
{
    float scaled_radius = (
        max_pixel_radius
        / max_measured_radius
        * measured_position.get_radius()
    );
    
    Polar_Vector_2D scaled_position {scaled_radius, measured_position.get_angle()};

    Quantized_Cartesian_Vector_2D result = scaled_position.make_cartesian().make_quantized();

    return result;
}