
"""
Unit tests for the oled screen.

Written for CircuitPython 9
"""

import time

import board
import displayio
import bitmaptools

from oled_display import OLED_Display


def test_oled_display():
    """
    Display hello world,
    wait 5 seconds,
    display white screen,
    wait 5 seconds.
    """
    
    i2c = board.I2C()
    oled_disp = OLED_Display(i2c)
    
    # Display "Hello, World!"
    oled_disp.add_text(
        "Hello, World!", 
        x=10, 
        y=10
    )

    time.sleep(5)
    oled_disp.make_new_canvas()

    # Display a white screen
    bitmap = displayio.Bitmap(
        oled_disp.screen_width, 
        oled_disp.screen_height, 
        oled_disp.num_colors,
    )
    bitmaptools.fill_region(
        bitmap, 
        x1=0, 
        y1=0, 
        x2=oled_disp.screen_width, 
        y2=oled_disp.screen_height,
        value=oled_disp.white_color_index
    )
    oled_disp.add_bitmap(bitmap)

    time.sleep(5)
