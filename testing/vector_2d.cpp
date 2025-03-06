
// 2D vector in polar coordinates.
// Angle must be in radians.


Polar_Vector_2D::Polar_Vector_2D(double r, double ang)
    :radius{r}, angle{ang}
{
}


double Polar_Vector_2D::calculate_cartesian_x()
{
    double result = radius * cos(angle);
    return result;
}


double Polar_Vector_2D::calculate_cartesian_y()
{
    double result = radius * sin(angle);
    return result;
}



