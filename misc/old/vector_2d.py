
"""
2D polar vector class.
"""

from math import cos, sin


class Polar_Vector_2D:
    """
    A 2D vector in polar coordinates.
    """
    def __init__(self, r, theta):
        self.r = r
        self.theta = theta
    
    def to_cartesian_x(self,):
        x = self.r * cos(self.theta)
        return x
    
    def to_cartesian_y(self,):
        y = self.r * sin(self.theta)
        return y