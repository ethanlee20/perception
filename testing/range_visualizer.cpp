

#include "vector_2d.hpp"
#include "range_visualizer.hpp"
// #include "oled_display.hpp"


Range_Visualizer::Range_Visualizer(
    double max_measured_radius
) : max_measured_radius {max_measured_radius}
{
    max_pixel_radius = (display.get_screen_height / 2) - 1;
    display.initialize();
}


void Range_Visualizer::clear()
{
    display.clear();
}


void Range_Visualizer::draw_dot_at(double measured_radius, double measured_angle)
{
    Polar_Vector_2D measured_position {measured_radius, measured_angle};
    Quantized_Cartesian_Vector_2D pixel_position = convert_to_pixel_position(
        measured_position
    );
    display.add_pixel(pixel_position.x, -pixel_position.y);
}


Quantized_Cartesian_Vector_2D Range_Visualizer::convert_to_pixel_position(
    Polar_Vector_2D measured_position
)
{
    double scaled_radius = (
        max_pixel_radius
        / max_measured_radius
        * measured_position.radius
    );
    
    Polar_Vector_2D scaled_position {scaled_radius, measured_position.angle};

    Quantized_Cartesian_Vector_2D result = scaled_position.make_cartesian().make_quantized();

    return result;
}