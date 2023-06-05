
/* Includes ------------------------------------------------------------------*/
#include "EE-API.h"

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

int API_clear_screen(uint8_t color)
{
	UB_VGA_FillScreen(color);

}



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
}


//int API_draw_circle(uint16_t x_c, uint16_t y_c, uint16_t radius, uint8_t color)
//{
//	int i;
//	int j;
//	int rads;
//	int rad = 0;
//	int x_c2 = x_c;
//	int y_c2 = y_c;
//
//
//
//	for (j = 0; j <= radius * 2; j++)
//	{
//		for(i = 0; i <= radius * 2; i++)
//		{
//			rads = (pow(i, 2) + pow(j, 2));
//			rad = sqrt(rads);
//
//			if(rad == radius)
//			{
//				UB_VGA_SetPixel((x_c2 - radius + i), (y_c2 - radius + j), color);
//			}
//			x_c++;
//		}
//		x_c = x_c2;
//		y_c++;
//	}
//
//}

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

}


int API_draw_text(uint16_t x, uint16_t y, uint8_t kleur, char* tekst, char* fontnaam,uint8_t fontgrootte,char* fontstijl)
{
	uint8_t i;
	uint16_t xd = x;
	uint16_t yd = y;
	uint16_t* cord_p;
	unsigned char letter_style;
	if(strcmp(fontnaam, "arial")  == 0)
	{
		letter_style = ARIAL;
	}
	else if(strcmp(fontnaam, "consolas")  == 0)
	{
		letter_style = CONSOLAS;
	}
		for(i = 0; tekst[i] != '\0'; i++)
		{
			switch(fontstijl[0])
			{
			case 'n':
				cord_p = draw_normal_letter(tekst[i], letter_style, xd, yd, fontgrootte, kleur, cord_p);
				xd = cord_p[0];
				yd = cord_p[1];
				break;
			case 'v':
				cord_p = draw_fat_letter(tekst[i], letter_style, xd, yd, fontgrootte, kleur, cord_p);
				xd = cord_p[0];
				yd = cord_p[1];
				break;
			case 'c':
				cord_p = draw_cursive_letter(tekst[i], letter_style, xd, yd, fontgrootte, kleur, cord_p);
				xd = cord_p[0];
				yd = cord_p[1];
				break;
			}
		}
	return 0;//returns error
}

uint16_t * draw_normal_letter(unsigned char letter, unsigned char letter_type, uint16_t xd, uint16_t yd,uint8_t fontgrootte, uint8_t kleur, uint16_t* cord_p)
{
    uint16_t end_cords[2];
    uint16_t begin_x = xd;
    int x_counter;
    int y_counter;
    int width;
    const uint8_t* glyph;
    int start_letter;

    if(letter_type == ARIAL)
    {
    	start_letter= arial_glyph_dsc[letter-32][1];
		glyph = &arial_glyph_bitmap[start_letter];
		width = arial_glyph_dsc[letter-32][0];
    }
    else if(letter_type == CONSOLAS)
	{
    	start_letter= consolas_glyph_dsc[letter-32][1];
		glyph = &consolas_glyph_bitmap[start_letter];
		width = consolas_glyph_dsc[letter-32][0];
	}
    //next line test
        if(xd+width >= VGA_DISPLAY_X)
        {
        	yd+=LETTER_BITMAP_HEIGHT;
        	begin_x=5;//sets x value to the left +5 pixels
        }
    //end test
    if(width%8)
    	width += 8;
    width = (width/8);


    for (y_counter = 0; y_counter < LETTER_BITMAP_HEIGHT; y_counter++) //goes trough every vertical layer of the bitmap
    {
        xd = begin_x;
        for (x_counter = 0; x_counter < width; x_counter++) //goes trough every horizontal layer of the bitmap
        {
        	for (int i = 7; i >= 0; i--)
        	{
				if ((glyph[((y_counter+1)*width)+x_counter] >> i) & 1)
					UB_VGA_SetPixel(xd, yd, kleur);
				xd++;
        	}
        }
        yd++;
        if (fontgrootte == SIZE_1)//skips one pixel of bitmap to shorten the letter by half
            y_counter++;
    }
    end_cords[0] = xd;
    end_cords[1] = yd-LETTER_BITMAP_HEIGHT;
    cord_p = end_cords;
    return cord_p;
}

uint16_t * draw_cursive_letter(unsigned char letter, unsigned char letter_type, uint16_t xd, uint16_t yd,uint8_t fontgrootte, uint8_t kleur, uint16_t* cord_p)
{
	uint16_t end_cords[2];
	uint16_t begin_x = xd;
	int x_counter;
	int y_counter;
	int width;
	const uint8_t* glyph;
	int start_letter;
	int angle;

	if(letter_type == ARIAL)
	{
		start_letter= arial_glyph_dsc[letter-32][1];
		glyph = &arial_glyph_bitmap[start_letter];
		width = arial_glyph_dsc[letter-32][0];
	}
	else if(letter_type == CONSOLAS)
	{
		start_letter= consolas_glyph_dsc[letter-32][1];
		glyph = &consolas_glyph_bitmap[start_letter];
		width = consolas_glyph_dsc[letter-32][0];
	}
	//next line test
		if(xd+width*2 >= VGA_DISPLAY_X)
		{
			yd+=LETTER_BITMAP_HEIGHT;
			begin_x=5;//sets x value to the left +5 pixels
		}
	//end test
	if(width%8)
		width += 8;
	angle = width; //sets angle offset for cursive letter
	if(fontgrootte == SIZE_1)
		angle = angle/2;
	width = (width/8);
	for(y_counter = 0; y_counter < LETTER_BITMAP_HEIGHT; y_counter++)
	{
		xd = begin_x;
		for(x_counter = 0; x_counter < width; x_counter++)
		{
			for (int i = 7; i >= 0; i--)
			{
				if ((glyph[((y_counter+1)*width)+x_counter] >> i) & 1)
					UB_VGA_SetPixel(xd+angle, yd, kleur);
				xd++;
			}
		}
		angle--; //decreases offset for each y layer to create an angle
		yd++;
		if(fontgrootte == SIZE_1)
			y_counter++;
	}
	end_cords[0] = xd;
    end_cords[1] = yd-LETTER_BITMAP_HEIGHT;
    cord_p = end_cords;
    return cord_p;
}


uint16_t * draw_fat_letter(unsigned char letter, unsigned char letter_type, uint16_t xd, uint16_t yd,uint8_t fontgrootte, uint8_t kleur, uint16_t* cord_p)
{
	uint16_t end_cords[2];
	uint16_t begin_x = xd;
	int x_counter;
	int y_counter;
	int width;
	const uint8_t* glyph;
	int start_letter;

	if(letter_type == ARIAL)
	{
		start_letter= arial_glyph_dsc[letter-32][1];
		glyph = &arial_glyph_bitmap[start_letter];
		width = arial_glyph_dsc[letter-32][0];
	}
	else if(letter_type == CONSOLAS)
	{
		start_letter= consolas_glyph_dsc[letter-32][1];
		glyph = &consolas_glyph_bitmap[start_letter];
		width = consolas_glyph_dsc[letter-32][0];
	}
	//next line test
	if(xd+width+THICKNESS >= VGA_DISPLAY_X)
	{
		yd+=LETTER_BITMAP_HEIGHT;
		begin_x=5;//sets x value to the left +5 pixels
	}
//end test
	if(width%8)
		width += 8;
	width = (width/8);

	for (y_counter = 0; y_counter < LETTER_BITMAP_HEIGHT; y_counter++) //goes trough every vertical layer of the bitmap
	{
		xd = begin_x;
		for (x_counter = 0; x_counter < width; x_counter++) //goes trough every horizontal layer of the bitmap
		{
			for (int i = 7; i >= 0; i--)
			{
				if ((glyph[((y_counter+1)*width)+x_counter] >> i) & 1)
				{
					UB_VGA_SetPixel(xd, yd, kleur);
					xd++;
					UB_VGA_SetPixel(xd, yd, kleur);
					xd++;
					UB_VGA_SetPixel(xd, yd, kleur);
					xd-=2;
				}
				xd++;
			}
		}
		yd++;
		if (fontgrootte == SIZE_1)//skips one pixel of bitmap to shorten the letter by half
			y_counter++;
	}
	end_cords[0] = xd;
    end_cords[1] = yd-LETTER_BITMAP_HEIGHT;
    cord_p = end_cords;
	return cord_p;
}





/*****************************************************************************
 *
 * @brief This function lets the user select an bitmap from the SD card, This bitmap will be pushed to the VGA screen
 *
 * @param *nr This variable selects wich bitmap will be displayed
 * @param x_lup This variable sets the starting x coordinate for the bitmap
 * @param y_lup This variable sets the starting y coordinate for the bitmap
 *
 *
 * @return Returns an error if error or returns nothing
 *
 *****************************************************************************/
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
    if (fres != FR_OK)
    {
    	printf("f_mount error (%i)\r\n", fres);
    	return 0; //error
    }

	fres = f_open(&fil, File, FA_READ);
	if (fres != FR_OK)
	{
		printf("f_open error (%i)\r\n",fres);
		return 0; //error
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


/*****************************************************************************
 *
 * @brief This function lets the user blur the screen using a filter kernel
 *
 * @return Returns an error if error or returns nothing
 *
 *****************************************************************************/
int API_blur_screen()
{
	uint16_t xp, yp;
	uint16_t xp_2, yp_2;
	uint16_t sum = 0;
	int i = 0;
	for (yp = 0; yp < VGA_DISPLAY_Y; yp++)
	{
	  for (xp = 0; xp < VGA_DISPLAY_X; xp++)
	  {
	    sum = 0;
	    i = 0;
	    for (yp_2 = yp; yp_2 < yp + 3 && yp_2 < VGA_DISPLAY_Y; yp_2++)
	    {
	      for (xp_2 = xp; xp_2 < xp + 3 && xp_2 < VGA_DISPLAY_X; xp_2++)
	      {
	        sum += VGA_RAM1[(yp_2 * (VGA_DISPLAY_X + 1)) + xp_2];
	        i++;
	      }
	    }
	    sum /= 9;
	    for (yp_2 = yp; yp_2 < yp + 3 && yp_2 < VGA_DISPLAY_Y; yp_2++)
	    {
	      for (xp_2 = xp; xp_2 < xp + 3 && xp_2 < VGA_DISPLAY_X; xp_2++)
	      {
	        VGA_RAM1[(yp_2 * (VGA_DISPLAY_X + 1)) + xp_2] = sum;
	      }
	    }
	  }
	}
	return 0;
	}

/*****************************************************************************
 *
 * @brief
 *
 * @param
 *
 * @return
 *
 *****************************************************************************/
unsigned int wacht(uint16_t msecs)
{
	HAL_Delay(msecs);
	return 1;
}






