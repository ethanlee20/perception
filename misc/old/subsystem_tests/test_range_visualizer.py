
"""
Test the range visualizer.

Requires working OLED display, ToF sensor, and encoder.

dun dun duuuuun
"""

import board
import adafruit_vl53l0x

from vector_2d import Polar_Vector_2D
from range_visualizer import Range_Visualizer


def test_range_visualizer():

    i2c = board.I2C()
    
    range_viz = Range_Visualizer(i2c, max_measured_radius=50)

    # this might not work
    # might need to initialize i2c different
    # for the sensor??
    vl53 = adafruit_vl53l0x.VL53L0X(i2c) 
    angle_encoder = ... # uh oh

    while True:

        measured_radius = vl53.range
        measured_angle = ... # uh oh
        print("Range: {0}mm".format(measured_radius))
        measured_position = Polar_Vector_2D(
            r=measured_radius,
            theta=measured_angle,
        )
        range_viz.draw(measured_position)


