
"""
2D vector class.
"""

from math import cos, sin


class Vector_2D:
    """
    A 2D vector in cartesian coordinates.

    Initialize from polar coordinates.
    """
    def __init__(self, r, theta):
        """
        Parameters
        ----------
        r : float
            Length of vector. 
        theta : float
            Vector's angle relative 
            (counterclockwise)
            to x-axis in radians.
        """
        self.x = r * cos(theta)
        self.y = r * sin(theta)
