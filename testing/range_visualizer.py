
"""
Visualizer for range finding.

Requires working OLED display and ToF sensor.
"""

import board
import displayio

from vector_2d import Polar_Vector_2D
from oled_display import OLED_Display


class Range_Visualizer:
    """
    Visualization tool for viewing
    ToF sensor data.
    """

    def __init__(
        self, 
        i2c:board.I2C, 
        max_measured_radius,
    ):
        """
        Initialize the range visualizer.
        """
        self.oled_display = OLED_Display(i2c)
        self.make_new_display_bitmap()

        self.max_pixel_radius = (
            (self.oled_display.screen_height / 2)  
            - 1
        )
        self.max_measured_radius = (
            max_measured_radius
        )

    def make_new_display_bitmap(self):
        """
        Make a new display bitmap.
        
        Write to this bitmap to draw
        things on the screen.
        """
        self.display_bitmap = displayio.Bitmap(
            self.oled_display.screen_width, 
            self.oled_display.screen_height, 
            self.oled_display.num_colors,
        )
        self.oled_display.add_bitmap(
            self.display_bitmap
        )

    def to_pixel_coordinates(
        self, 
        measured_position:Polar_Vector_2D,
    ):
        """
        Convert a measured position to 
        (quantized) pixel coordinates.

        The position should be given as a 
        2D vector in Cartesian coordinates.

        The origin is the middle of the screen.
        """

        pixel_radius = (
            self.max_pixel_radius
            / self.max_measured_radius
            * measured_position.r
        )
        pixel_polar_position = Polar_Vector_2D(
            r=pixel_radius,
            theta=measured_position.theta,
        )

        pixel_x = int(
            pixel_polar_position
            .to_cartesian_x()
            + (self.oled_display.screen_width / 2)
        )
        pixel_y = - int(
            pixel_polar_position
            .to_cartesian_y()
            + (self.oled_display.screen_height / 2)
        )
        return pixel_x, pixel_y
    
    def draw(
        self, 
        measured_position:Polar_Vector_2D
    ):
        pixel_x, pixel_y = self.to_pixel_coordinates(
            measured_position
        )
        self.display_bitmap[pixel_x, pixel_y]




















# def quantize(
#         x:float, 
#         resolution:int, 
#         interval:tuple[float],
# ):
#     """
#     Quantize a float over a specified interval.

#     Parameters
#     ----------
#     x : float
#         Number to be quantized.
#     resolution : int
#         Number of possible values.
#     interval : tuple[float]
#         (Minimum, maximum) of the interval.
    
#     Returns
#     -------
#     space_index : int
#         Quantized space index.
#     """
#     interval_width = interval[1] - interval[0]
#     x_scaled_and_shifted = (
#         (x - interval[0]) 
#         * resolution / interval_width
#     )
#     space_index = int(x_scaled_and_shifted)
#     return space_index


# class Rectangle:
#     """
#     A rectangle.
#     """
#     def __init__(self, width, height):
#         self.width = width
#         self.height = height


    
# class Display:
#     """
#     A simple display for the command line.

#     The origin of the coordinate system is
#     at the middle of the display.
#     """

#     def __init__(
#         self, 
#         width:float,
#         height:float,
#         resolution:int, 
#         empty_char='-',
#         full_char='*',
#     ):
#         """
#         Parameters
#         ----------
#         width : float
#         height : float 
#         resolution : int
#             The number of spaces per dimension.
#         empty_char : str
#             The thing to draw at empty spaces.
#         full_char : str
#             The thing to draw at full spaces.
            
#         """
#         self.empty_char = empty_char
#         self.full_char = full_char
#         self.resolution = resolution
#         self.dimensions = Rectangle(
#             width, 
#             height
#         )
#         self.x_interval = (
#             -width/2, 
#             width/2
#         )
#         self.y_interval = (
#             -height/2, 
#             height/2
#         )

#         self.grid = self.create_empty_grid()

#     def create_empty_grid(self,):
#         empty_grid = [
#             [
#                 self.empty_char 
#                 for col in 
#                 range(self.resolution)
#             ] 
#             for row in 
#             range(self.resolution)
#         ]
#         return empty_grid
    
#     def draw(self,):
#         output = '\n'.join(
#             [''.join(row) for row in self.grid]
#         )
#         print(output)
    
#     def clear_all(self,):
#         self.grid = self.create_empty_grid()

#     def set(self, position:Vector_2D):
#         column_index = quantize(
#             position.x, 
#             self.resolution, 
#             self.x_interval
#         )
#         row_index = quantize(
#             -position.y,
#             self.resolution, 
#             self.y_interval
#         )
#         (
#             self.grid
#             [row_index]
#             [column_index]
#         ) = self.full_char

# disp = Display(
#     width=11, 
#     height=11, 
#     resolution=50,
#     empty_char=' ',
# )

# steps = 100
# r = 5
# theta_values = [
#     (2*pi)*i/steps for i in range(steps)
# ]

# for theta in theta_values:
#     vec = Vector_2D(r, theta)
#     disp.set(vec)
#     disp.draw()
#     sleep(0.05)