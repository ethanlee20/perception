
"""
Test the Display class.
"""

from math import pi
from time import sleep

from vector_2d import Vector_2D
from display import Display


disp = Display(
    width=11, 
    height=11, 
    resolution=50,
    empty_char=' ',
)

steps = 100
r = 5
theta_values = [
    (2*pi)*i/steps for i in range(steps)
]

for theta in theta_values:
    vec = Vector_2D(r, theta)
    disp.set(vec)
    disp.draw()
    sleep(0.05)

