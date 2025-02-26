
"""
Display tof sensor measurements on the command line. 
"""

from vector_2d import Vector_2D


def quantize(
        x:float, 
        resolution:int, 
        interval:tuple[float],
):
    """
    Quantize a float over a specified interval.

    Parameters
    ----------
    x : float
        Number to be quantized.
    resolution : int
        Number of possible values.
    interval : tuple[float]
        (Minimum, maximum) of the interval.
    
    Returns
    -------
    space_index : int
        Quantized space index.
    """
    interval_width = interval[1] - interval[0]
    x_scaled_and_shifted = (
        (x - interval[0]) 
        * resolution / interval_width
    )
    space_index = int(x_scaled_and_shifted)
    return space_index


class Rectangle:
    """
    A rectangle.
    """
    def __init__(self, width, height):
        self.width = width
        self.height = height


    
class Display:
    """
    A simple display for the command line.

    The origin of the coordinate system is
    at the middle of the display.
    """

    def __init__(
        self, 
        width:float,
        height:float,
        resolution:int, 
        empty_char='-',
        full_char='*',
    ):
        """
        Parameters
        ----------
        width : float
        height : float 
        resolution : int
            The number of spaces per dimension.
        empty_char : str
            The thing to draw at empty spaces.
        full_char : str
            The thing to draw at full spaces.
            
        """
        self.empty_char = empty_char
        self.full_char = full_char
        self.resolution = resolution
        self.dimensions = Rectangle(
            width, 
            height
        )
        self.x_interval = (
            -width/2, 
            width/2
        )
        self.y_interval = (
            -height/2, 
            height/2
        )

        self.grid = self.create_empty_grid()

    def create_empty_grid(self,):
        empty_grid = [
            [
                self.empty_char 
                for col in 
                range(self.resolution)
            ] 
            for row in 
            range(self.resolution)
        ]
        return empty_grid
    
    def draw(self,):
        output = '\n'.join(
            [''.join(row) for row in self.grid]
        )
        print(output)
    
    def clear_all(self,):
        self.grid = self.create_empty_grid()

    def set(self, position:Vector_2D):
        column_index = quantize(
            position.x, 
            self.resolution, 
            self.x_interval
        )
        row_index = quantize(
            -position.y,
            self.resolution, 
            self.y_interval
        )
        (
            self.grid
            [row_index]
            [column_index]
        ) = self.full_char

