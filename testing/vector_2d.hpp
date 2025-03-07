
// 2D vectors.
// Angle must be in radians.


#ifndef vector_2d_h
#define vector_2d_h


class Quantized_Cartesian_Vector_2D 
{
    public:
        Quantized_Cartesian_Vector_2D(int x, int y)
            :x{x}, y{y} {}
        int get_x(){return x;}
        int get_y(){return y;}
    
    private:
        int x, y;
};


class Cartesian_Vector_2D 
{
    public:
        Cartesian_Vector_2D(double x, double y)
            :x{x}, y{y} {}
        double get_x(){return x;}
        double get_y(){return y;}
        Quantized_Cartesian_Vector_2D make_quantized();
    
    private:
        double x, y;
};


class Polar_Vector_2D 
{
    public:
    Polar_Vector_2D(float radius, float angle)
            :radius{radius}, angle{angle} {}
        float get_radius() {return radius;}
        float get_angle() {return angle;}
        Cartesian_Vector_2D make_cartesian();

    private:
        double radius, angle;
};



#endif