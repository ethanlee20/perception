// test for the range visualizer


#include "range_visualizer.hpp"


const double max_measured_radius {200}; // in mm?
Range_Visualizer range_viz {max_measured_radius};


void setup() 
{

    // Try on just fake data.
    // Should draw a circle on the display.

    range_viz.initialize();

    const double radius {150}; // in mm?

    for (
        double angle = 0; 
        angle < (2 * M_PI); 
        angle += 0.1
    )
    {
        range_viz.draw_dot_at(radius, angle);
        delay(100);
    }
    delay(500);
    range_viz.clear(); // clear screen.

}
  
void loop() 
{
    // put your main code here, to run repeatedly:
  
}