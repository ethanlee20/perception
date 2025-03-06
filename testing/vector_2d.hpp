
// 2D vector in polar coordinates.
// Angle must be in radians.


#ifndef vector_2d_h
#define vector_2d_h


class Polar_Vector_2D {

    public:
        Polar_Vector_2D(double r, double ang);
        double get_radius() {return radius;}
        double get_angle() {return angle;}
        double calculate_cartesian_x();
        double calculate_cartesian_y();

    private:
        double radius, angle;

};


#endif