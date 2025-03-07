
// 2D vector in polar coordinates.
// Angle must be in radians.

#include "vector_2d.hpp"


Cartesian_Vector_2D Polar_Vector_2D::make_cartesian()
{
    double x = radius * cos(angle);
    double y = radius * sin(angle);
    Cartesian_Vector_2D result {x, y};
    return result;
}


Quantized_Cartesian_Vector_2D Cartesian_Vector_2D::make_quantized()
{
    int x_quant = x; // implicit type narrowing :)
    int y_quant = y;
    Quantized_Cartesian_Vector_2D result {x_quant, y_quant};
    return result;
}


