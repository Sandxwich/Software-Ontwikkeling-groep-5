
/* Includes ------------------------------------------------------------------*/
#include "EE-API.h"


/**********************************************************************//**
@brief This function lets the user draw a line on a VGA screen

@param x_1
@param y_1
@param x_2
@param y_2
@param dikte this variable sets the thickness of the line
@param color This variable sets the color for the screen

@return Returns bitman
@return Returns an error if error or returns nothing


 *************************************************************************/

int API_draw_line(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint8_t dikte, uint8_t color)
{
	int error = 0;
	//error checks
//	if(checkcolor(color))
//		return error;

	int dx = x_2 - x_1;
	int dy = y_2 - y_1;
	int steps;
	if(abs(dx)>abs(dy))
	{
		steps = abs(dx);
	}
	else if(abs(dy)>abs(dx))
	{
		steps = abs(dy);
	}

	float xIncrement = (float) dx / steps;
	float yIncrement = (float) dy / steps;
	int i;

	// Set the pixels along the center line of the given thickness
	for (i = 0-abs(dikte/2); i <= abs(dikte/2); i++) {
		float x = x_1 + 0.5;
		float y = y_1 + i + 0.5;
		int j;
		for (j = 0; j < steps; j++) {
			UB_VGA_SetPixel(x, y, color);
			x += xIncrement;
			y += yIncrement;
		}
	}
	return error;
}

/**********************************************************************//**
@brief This function lets the user clear a VGA screen

@param color This variable sets the color for the screen


@return Returns an error if error or returns nothing


 *************************************************************************/

int API_clear_screen(uint8_t color)
{
	UB_VGA_FillScreen(color);

	return 0;
}


/**********************************************************************//**
@brief This function lets the user draw a rectangle on a VGA screen

@param x_lup This variable sets the starting x coordinate for the rectangle
@param y_lup This variable sets the starting y coordinate for the rectangle
@param breedte This variable sets the width for the rectangle
@param hoogte This variable sets the height for the rectangle
@param color This variable sets the color for the rectangle
@param gevuld This variable decides if the rectangle is filled or not (filled = 1, not filled = 0)


@return Returns an error if error or returns nothing


 *************************************************************************/

int API_draw_rectangle(uint16_t x_lup, uint16_t y_lup, uint16_t breedte, uint16_t hoogte, uint8_t color, uint8_t gevuld)
{
	int xp = 0;
	int yp = 0;

	//draw lines along screen every y-value
	if(gevuld == 1)
	{
		for(yp = y_lup; yp < y_lup + hoogte; yp++)
		{
			for(xp = x_lup; xp < x_lup + breedte; xp++)
			{
				UB_VGA_SetPixel(xp, yp, color);
			}
		}
	}

	else if(gevuld == 0)
	{

			for(yp = y_lup; yp <= y_lup + hoogte; yp++)
			{
				for(xp = x_lup; xp <= x_lup + breedte; xp++)
				{
					//draw lines along screen every y-value
					if ((yp == y_lup) || (yp == (y_lup + hoogte)))
					{
						UB_VGA_SetPixel(xp, yp, color);
					}

					//Draw pixels along screen only at edges
					else if((xp == x_lup) || (xp == (x_lup + breedte)))
					{
						UB_VGA_SetPixel(xp, yp, color);
					}
				}
			}
	}
	return 0;
}


/**********************************************************************//**
@brief This function lets the user draw a circle on a VGA screen

@param x_c This variable sets the starting x coordinate for the circle
@param y_c This variable sets the starting y coordinate for the circle
@param radius This variable sets the radius for the circle
@param color This variable sets the color for the circle


@return Returns an error if error or returns nothing


 *************************************************************************/

int API_draw_circle(uint16_t x_c, uint16_t y_c, uint16_t radius, uint8_t color)
{
    int i;
    int j;
    int rads;
    int rad = 0;


    for (j = -radius; j <= radius; j++)
    {
        for (i = -radius; i <= radius; i++)
        {
            rads = (pow(i, 2) + pow(j, 2));
            rad = sqrt(rads);

            if (rad == radius)
            {
                UB_VGA_SetPixel((x_c + i), (y_c + j), color);
            }
        }
    }
    return 0;
}


/**********************************************************************//**
@brief

@param nr
@param x_lup
@param y_lup


@return Returns an error if error or returns nothing


 *************************************************************************/

int API_draw_bitmap(uint16_t nr, uint16_t x_lup, uint16_t y_lup)
{
	int error = 0;
	uint16_t xp,yp,xp2,yp2 = 0;
	yp2=0;
	  for(yp = 20; yp < 120; yp++)
	  {
	    for(xp = 0, xp2 = 0; xp < 100; xp++)
	    {
	      UB_VGA_SetPixel(xp, yp, bitmap[yp2][xp2]);
	      xp2++;
	    }
	    yp2++;
	  }

	return error;
}

/**********************************************************************//**
@brief

@param nr
@param x_lup
@param y_lup


@return Returns an error if error or returns nothing

 *************************************************************************/

int API_read_bitmap_SD(char *nr, uint16_t x_lup, uint16_t y_lup)
{

	// Fatfs variables
	FATFS FatFs;
    FIL fil; 		//File handle
    FRESULT fres; 	//Result after operations
    UINT SizeofBuffer = 30;

    //Reading buffer
    uint k = 0; // kijken welk variable we zijn

    //Position vga
    uint16_t xp,yp,xp2,yp2;

    xp2 = 0;
    yp2 = 0;

    //Information from file system
    unsigned int Height,Width;

    //Creating decimal shift register
	unsigned int ColourFile = 0;
	unsigned int DecimalshiftBuff = 0;


	unsigned char i;

	char readBuf[30];

	TCHAR File[] = "00.txt";

	File[0] = nr[0];		// checked
	File[1] = nr[1];

	xp = x_lup;
	yp = y_lup;


    fres = f_mount(&FatFs, "", 1); //1=mount now
    if (fres != FR_OK) {
   	printf("f_mount error (%i)\r\n", fres);
   	while(1);
    }

	fres = f_open(&fil, File, FA_READ);
	if (fres != FR_OK) {
	printf("f_open error (%i)\r\n",fres);
	while(1);
	}


	while (SizeofBuffer == 30)
	{
		f_read(&fil,(void*)readBuf, 30, &SizeofBuffer);
		for (i=0; i<SizeofBuffer; i++)
		{

			if (readBuf[i] != 32)
			{
				DecimalshiftBuff = readBuf[i]-'0';
				ColourFile *= 10;
				ColourFile += DecimalshiftBuff;
			}

			else if(readBuf[i] == 32)
			{
				if (k > 1)
				{
					if (xp < VGA_DISPLAY_X && yp < VGA_DISPLAY_Y)
					{
						VGA_RAM1[(yp * (VGA_DISPLAY_X + 1)) + xp] = ColourFile;
					}

					UB_VGA_SetPixel(xp, yp, ColourFile);
					xp++;
					xp2++;
					if (xp2 >= Width)
					{
						yp++;
						yp2++;
						xp = x_lup;
						xp2 = 0;
					}
					if (yp2 == Height)
					{
						break;
					}
				}
				else if (k == 0) // Hoogte van de bit map
				{
					Height = ColourFile;
				}
				else if (k == 1)
				{
					Width = ColourFile;
				}

				k++;
				ColourFile = 0;
			}

		}
	}

	f_close(&fil);

    f_mount(NULL, "", 0);

	return 0;
}

/**********************************************************************//**
@brief This function sets an integer to Ascii

@param number

@return Returns ascii value

 *************************************************************************/

int intToAscii(int number)
{
   return '0' + number;
}

