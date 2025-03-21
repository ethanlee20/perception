
"""
OLED Display class.

Written for CircuitPython 9.
"""

import board
import displayio
import i2cdisplaybus
import adafruit_displayio_ssd1306
import terminalio
from adafruit_display_text import label


class OLED_Display:
    
    def __init__(self, i2c:board.I2C):
        """
        Initialize display.
        """
    
        self.device_address = 0x3d
        self.screen_width = 128
        self.screen_height = 64
        self.num_colors = 2 # black and white
        self.black_color = 0x000000
        self.black_color_index = 0
        self.white_color = 0xFFFFFF
        self.white_color_index = 1

        self.connect_display(i2c)
        self.init_color_palette()
        self.make_new_canvas()

    def connect_display(self, i2c):
        """
        Connect to the display over I2C.
        """

        displayio.release_displays()

        display_bus = i2cdisplaybus.I2CDisplayBus(
            i2c, 
            device_address=self.device_address
        )

        self.display = adafruit_displayio_ssd1306.SSD1306(
            display_bus, 
            width=self.screen_width, 
            height=self.screen_height,
        )
        
    def init_color_palette(self):
        """
        Initialize color things.
        """
        self.color_palette = displayio.Palette(
            self.num_colors
        )
        self.color_palette[self.black_color_index] = (
            self.black_color
        )
        self.color_palette[self.white_color_index] = (
            self.white_color
        )

    def make_new_canvas(self,):
        """
        (re)Initialize canvas (drawing area).
        """
        self.canvas = displayio.Group()
        self.display.root_group = self.canvas

    def add_bitmap(self, bitmap):
        """Add a bitmap to the canvas"""
        tile_grid = displayio.TileGrid(
            bitmap, 
            pixel_shader=self.color_palette, 
        )
        self.canvas.append(tile_grid)
    
    def add_text(self, text:str, x:int, y:int):
        """Add text to the canvas. (In white.)"""
        text_sprite = label.Label(
            terminalio.FONT, 
            text=text, 
            color=self.white_color,
        )
        text_sprite.x = x
        text_sprite.y = y
        self.canvas.append(text_sprite)
