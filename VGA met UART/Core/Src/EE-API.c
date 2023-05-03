
/* Includes ------------------------------------------------------------------*/
#include "EE-API.h"

// Define the image dimensions
#define WIDTH  256
#define HEIGHT 256

// Define the image data as a global array
unsigned char image[WIDTH * HEIGHT * 3];

/*
 * int API_draw_line(int x_1, y_1, x_2, y2, color, dikte)
 *
 * inputs:
 * 	x_1:
 * 	y_1:
 * 	x_2:
 * 	y_2:
 * 	color:
 * 	dikte:
 *
 * outputs:
 * 	error:
 * 	bitmap:
 *
 */

int API_draw_line(int x_1, y_1, x_2, y2, color, dikte)
{
	int error = NULL;
	//error checks
	if(checkcolor(color))
		return error;

	int dx = abs(x1 - x0);
	    int dy = abs(y1 - y0);
	    int sx = (x0 < x1) ? 1 : -1;
	    int sy = (y0 < y1) ? 1 : -1;
	    int err = dx - dy;
	    int e2, x, y, i;

	    // Set the pixels along the center line of the given thickness
	    for (i = -thickness/2; i <= thickness/2; i++) {
	        x = x0;
	        y = y0 + i;
	        while (1) {
	            setPixel(x, y, color);
	            if (x == x1 && y == y1) {
	                break;
	            }
	            e2 = 2 * err;
	            if (e2 > -dy) {
	                err -= dy;
	                x += sx;
	            }
	            if (e2 < dx) {
	                err += dx;
	                y += sy;
	            }
	        }
	    }

	return error;
}

void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    int index = (y * WIDTH + x) * 3;
    image[index] = r;
    image[index + 1] = g;
    image[index + 2] = b;
}
