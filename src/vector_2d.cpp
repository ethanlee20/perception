
// 2D vector in polar coordinates.
// Angle must be in radians.

#include "vector_2d.hpp"
#include <Arduino.h>


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


/**
 * @brief applies a homogeneneous transformation
 * useful for mapping robot frame points (spinning lidar) to world frame
 * 
 * @param point_in_ref 
 * @param rotation_offset_deg 
 * @param translation_offset_x 
 * @param translation_offset_y 
 * @return Cartesian_Vector_2D 
 */
Cartesian_Vector_2D apply_homogeneous_transformation(
    Polar_Vector_2D point_in_ref,
    double rotation_offset_deg,
    double translation_offset_x,
    double translation_offset_y
){
    Cartesian_Vector_2D point_in_ref_car = point_in_ref.make_cartesian();

    double rotation_rad = rotation_offset_deg * M_PI / 180.0;  // Convert degrees to radians
    double cos_phi = cos(rotation_rad);
    double sin_phi = sin(rotation_rad);
    
    double x_new = cos_phi * point_in_ref_car.get_x() - sin_phi * point_in_ref_car.get_y() + translation_offset_x;
    double y_new = sin_phi * point_in_ref_car.get_y() + cos_phi * point_in_ref_car.get_x() + translation_offset_y;

    return Cartesian_Vector_2D {x_new, y_new};
}
