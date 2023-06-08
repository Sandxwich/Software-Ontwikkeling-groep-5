
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : EE-API.c
  * @brief          : File that serves as VGA library
  ******************************************************************************
  * @attention
  *******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "EE-API.h"

/*****************************************************************************//*
 *
 * @brief Deze functie tekent een lijn van 2 coordinaten
 * 		  Dit wordt gedaan aan de hand van  Bresenham algoritme
 *
 * @param x_1: begin x coordinaat van de lijn
 * @param y_1: begin y coordinaat van de lijn
 * @param x_2: eind x coordinaat van de lijn
 * @param y_2: eind y coordinaat van de lijn
 * @param dikte: hoeveel pixels breed de lijn moet zijn
 * @param color: kleur van de tekst
 *
 *****************************************************************************/

int API_draw_line(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint8_t dikte, uint8_t color)
{
	int error = 0;
	int dx = x_2 - x_1;
	int dy = y_2 - y_1;
	int steps;
	if(dx>dy)
	{
		steps = abs(dx);
	}
	else if(dy>dx)
	{
		steps = abs(dy);
	}
	else if (dx == dy)
	{
		steps = abs(dy);
	}
	else if(abs(dx)==abs(dy))
		steps = abs(dy);
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

}

/*****************************************************************************//*
 *
 * @brief This function looks at the incomming string and checks what kind of font and style it wants
 *
 * @param x: begin x coordinaat van de zin
 * @param y: begin y coordinaat van de zin
 * @param kleur: kleur van de tekst
 * @param tekst: een pointer naar de string die wordt uitgelezen
 * @param fontnaam: de naam van de font die gekozen wordt [consolas, arial]
 * @param fontgroote: de size van de tekst [1,2]
 * @param fontstijl: de stijl waarin de tekst geprint word [normaal, cursief, vet]
 *
 *****************************************************************************/
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
	else
	{
		API_err_handler(UNKNOWN_FONT);
		return 0;
	}
	for(i = 0; tekst[i] != '\0'; i++)
	{
		if(tekst[i] < ASCII_START ||tekst[i] > 127)
		{
			API_err_handler(NOT_VALID_CHAR);
			return 0;
		}
		switch(fontstijl[0])
		{
		case 'n':
			cord_p = draw_normal_letter(tekst[i], letter_style, xd, yd, fontgrootte, kleur, cord_p);
			if(cord_p == 0)
				return 0;
			xd = cord_p[0];
			yd = cord_p[1];
			break;
		case 'v':
			cord_p = draw_fat_letter(tekst[i], letter_style, xd, yd, fontgrootte, kleur, cord_p);
			if(cord_p == 0)
				return 0;
			xd = cord_p[0];
			yd = cord_p[1];
			break;
		case 'c':
			cord_p = draw_cursive_letter(tekst[i], letter_style, xd, yd, fontgrootte, kleur, cord_p);
			if(cord_p == 0)
				return 0;
			xd = cord_p[0];
			yd = cord_p[1];
			break;
		default:
			API_err_handler(UNKNOWN_FONT_STYLE);
			return 0;
			break;
		}
	}
	return 0;
}

/*****************************************************************************//*
 *
 * @brief This function prints the letter normally
 *
 * @param Same params as API_draw_text but with an pointer to the starting coordinates for each letter
 *
 * @return Returns the last coordinates that the letter was printed
 *
 *****************************************************************************/
uint16_t * draw_normal_letter(unsigned char letter, unsigned char letter_type, uint16_t xd, uint16_t yd,uint8_t fontgrootte, uint8_t kleur, uint16_t* cord_p)
{
    uint16_t end_cords[2];
    uint16_t begin_x = xd;
    int x_counter;
    int y_counter;
    int width;
    const uint8_t* glyph;
    int start_letter;
	uint8_t bitmap_height;
	if(letter_type == ARIAL)
	{
		if(fontgrootte == SIZE_1)
		{
			start_letter= arial_24_glyph_dsc[letter-ASCII_START][1];
			glyph = &arial_24_glyph_bitmap[start_letter];
			width = arial_24_glyph_dsc[letter-ASCII_START][0];
			bitmap_height = LETTER_SIZE_1_HEIGHT;
		}
		else if(fontgrootte == SIZE_2)
		{
			start_letter= arial_glyph_dsc[letter-32][1];
			glyph = &arial_glyph_bitmap[start_letter];
			width = arial_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_2_HEIGHT;
		}
		else
		{
			API_err_handler(UNKNOWN_FONT_SIZE);
			return 0;
		}
	}
	else if(letter_type == CONSOLAS)
	{
		if(fontgrootte == SIZE_1)
		{
			start_letter= consolas_24_glyph_dsc[letter-32][1];
			glyph = &consolas_24_glyph_bitmap[start_letter];
			width = consolas_24_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_1_HEIGHT;
		}
		else if(fontgrootte == SIZE_2)
		{
			start_letter= consolas_glyph_dsc[letter-32][1];
			glyph = &consolas_glyph_bitmap[start_letter];
			width = consolas_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_2_HEIGHT;
		}
		else
		{
			API_err_handler(UNKNOWN_FONT_SIZE);
			return 0;
		}
	}
	if(xd+width >= VGA_DISPLAY_X)
	{
		yd+=bitmap_height;
		begin_x=5;//sets x value to the left +5 pixels
	}
	if(yd >= VGA_DISPLAY_Y)
	{
		API_err_handler(Y_TO_HIGH);
		return 0;
	}
    if(width%8)
    	width += 8;
    width = (width/8);


    for (y_counter = 0; y_counter < bitmap_height; y_counter++) //goes trough every vertical layer of the bitmap
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
    }
    end_cords[0] = xd;
    end_cords[1] = yd-bitmap_height;
    cord_p = end_cords;
    return cord_p;
}

/*****************************************************************************//*
 *
 * @brief This function prints the letter but adds an angle by offsetting the x value and decreasing this offset each y layer
 *
 * @param Same params as API_draw_text but with an pointer to the starting coordinates for each letter
 *
 * @return Returns the last coordinates that the letter was printed
 *
 *****************************************************************************/
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
	uint8_t bitmap_height;
	if(letter_type == ARIAL)
	{
		if(fontgrootte == SIZE_1)
		{
			start_letter= arial_24_glyph_dsc[letter-32][1];
			glyph = &arial_24_glyph_bitmap[start_letter];
			width = arial_24_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_1_HEIGHT;
		}
		else if(fontgrootte == SIZE_2)
		{
			start_letter= arial_glyph_dsc[letter-32][1];
			glyph = &arial_glyph_bitmap[start_letter];
			width = arial_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_2_HEIGHT;
		}
		else
		{
			API_err_handler(UNKNOWN_FONT_SIZE);
			return 0;
		}
	}
	else if(letter_type == CONSOLAS)
	{
		if(fontgrootte == SIZE_1)
		{
			start_letter= consolas_24_glyph_dsc[letter-32][1];
			glyph = &consolas_24_glyph_bitmap[start_letter];
			width = consolas_24_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_1_HEIGHT;
		}
		else if(fontgrootte == SIZE_2)
		{
			start_letter= consolas_glyph_dsc[letter-32][1];
			glyph = &consolas_glyph_bitmap[start_letter];
			width = consolas_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_2_HEIGHT;
		}
		else
		{
			API_err_handler(UNKNOWN_FONT_SIZE);
			return 0;
		}
	}
	if(xd+width*2 >= VGA_DISPLAY_X)
	{
		yd+=bitmap_height;
		begin_x=5;//sets x value to the left +5 pixels
	}
	if(yd >= VGA_DISPLAY_Y)
	{
		API_err_handler(Y_TO_HIGH);
		return 0;
	}
	if(width%8)
		width += 8;
	angle = width; //sets angle offset for cursive letter
	if(fontgrootte == SIZE_1)
		angle = angle/2;
	width = (width/8);
	for(y_counter = 0; y_counter < bitmap_height; y_counter++)
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
	}
	end_cords[0] = xd;
    end_cords[1] = yd-bitmap_height;
    cord_p = end_cords;
    return cord_p;
}

/*****************************************************************************//*
 *
 * @brief This function prints the letter with added pixels horizontally to create a fatter looking letter
 *
 * @param Same params as API_draw_text but with an pointer to the starting coordinates for each letter
 *
 * @return Returns the last coordinates that the letter was printed
 *
 *****************************************************************************/
uint16_t * draw_fat_letter(unsigned char letter, unsigned char letter_type, uint16_t xd, uint16_t yd,uint8_t fontgrootte, uint8_t kleur, uint16_t* cord_p)
{
	uint16_t end_cords[2];
	uint16_t begin_x = xd;
	int x_counter;
	int y_counter;
	int width;
	const uint8_t* glyph;
	int start_letter;
	uint8_t bitmap_height;

	if(letter_type == ARIAL)
	{
		if(fontgrootte == SIZE_1)
		{
			start_letter= arial_24_glyph_dsc[letter-32][1];
			glyph = &arial_24_glyph_bitmap[start_letter];
			width = arial_24_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_1_HEIGHT;
		}
		else if(fontgrootte == SIZE_2)
		{
			start_letter= arial_glyph_dsc[letter-32][1];
			glyph = &arial_glyph_bitmap[start_letter];
			width = arial_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_2_HEIGHT;
		}
		else
		{
			API_err_handler(UNKNOWN_FONT_SIZE);
			return 0;
		}
	}
	else if(letter_type == CONSOLAS)
	{
		if(fontgrootte == SIZE_1)
		{
			start_letter= consolas_24_glyph_dsc[letter-32][1];
			glyph = &consolas_24_glyph_bitmap[start_letter];
			width = consolas_24_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_1_HEIGHT;
		}
		else if(fontgrootte == SIZE_2)
		{
			start_letter= consolas_glyph_dsc[letter-32][1];
			glyph = &consolas_glyph_bitmap[start_letter];
			width = consolas_glyph_dsc[letter-32][0];
			bitmap_height = LETTER_SIZE_2_HEIGHT;
		}
		else
		{
			API_err_handler(UNKNOWN_FONT_SIZE);
			return 0;
		}
	}
	if(xd+width+THICKNESS >= VGA_DISPLAY_X)
	{
		yd+=bitmap_height;
		begin_x=5;//sets x value to the left +5 pixels
	}
	if(yd >= VGA_DISPLAY_Y)
	{
		API_err_handler(Y_TO_HIGH);
		return 0;
	}
	if(width%8)
		width += 8;
	width = (width/8);
	if(width == 0)
		width++;

	for (y_counter = 0; y_counter < bitmap_height; y_counter++) //goes trough every vertical layer of the bitmap
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
	}
	end_cords[0] = xd;
    end_cords[1] = yd-bitmap_height;
    cord_p = end_cords;
	return cord_p;
}





/*****************************************************************************//*
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
    	API_err_handler(NO_SD_CARD_DETECTED);
    	return 0; //error
    }

	fres = f_open(&fil, File, FA_READ);
	if (fres != FR_OK)
	{
		API_err_handler(UNKNOWN_BITMAP);
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


/*****************************************************************************//*
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

/*****************************************************************************//*
 *
 * @brief This function lets the user hold the program for a given miliseconds
 *
 * @param msecs Time that the program holds
 *
 * @return returns 0
 *
 *****************************************************************************/
unsigned int API_wacht(uint16_t msecs)
{
	HAL_Delay(msecs);
	return 0;
}

/*****************************************************************************//*
 *
 * @brief This function shows the user that they made an error, and what this error is
 *
 * @param API_err_in an errorcode thats defined in the API_error.h
 *
 * @return returns a message to the user
 *
 *****************************************************************************/
void API_err_handler(int API_err_in)
{
	switch(API_err_in)
	{
	case INVALID_MESSAGE:
		printf("dit bericht is niet volgens de richtlijnen, type help voor meer informatie ");
		printf("type help voor meer informatie\n");
		break;
	case X_OUT_OF_BOUNDS:
		printf("Een van de ingevulde X coordinaten is niet geldig, X mag niet groter zijn dan 320 ");
		printf("type help voor meer informatie\n");
		break;
	case Y_OUT_OF_BOUNDS:
		printf("Een van de ingevulde Y coordinaten is niet geldig, X mag niet groter zijn dan 240 ");
		printf("type help voor meer informatie\n");
		break;
	case NOT_A_NUMBER:
		printf("Op de plek waar je een getal in moet vullen heb je iets anders ingevuld ");
		printf("type help voor meer informatie\n");
		break;
	case NOT_A_CHARACTER:
		printf("Op de plek waar je een character in moet vullen heb je iets anders ingevuld ");
		printf("type help voor meer informatie\n");
		break;
	case UNKNOWN_COLOR:
		printf("de kleur die je hebt uitgekozen staat niet in de lijst van mogelijke kleuren ");
		printf("type help voor meer informatie\n");
		break;
	case UNKNOWN_BITMAP:
		printf("de bitmap die je zoekt staat niet het lijst van mogelijke bitmaps ");
		printf("type help voor meer informatie\n");
		break;
	case UNKNOWN_FONT:
		printf("de font die je invult is niet bekent. probeer arial of consolas ");
		printf("type help voor meer informatie\n");
		break;
	case UNKNOWN_FONT_SIZE:
		printf("de size die je hier invult is niet geldig. probeer 1 of 2 ");
		printf("type help voor meer informatie\n");
		break;
	case UNKNOWN_FONT_STYLE:
		printf("de stijl die je invult is niet bekent. probeer normaal, vet of cursief ");
		printf("type help voor meer informatie\n");
		break;
	case UNKNOWN_FUNCTION:
		printf("de functie die je invult bestaat niet ");
		printf("type help voor meer informatie\n");
		break;
	case Y_TO_HIGH:
		printf("de functie gaat de maximale y waarde voorbij ");
		printf("type help voor meer informatie\n");
		break;
	case X_TO_HIGH:
		printf("de functie gaat de maximale x waarde voorbij ");
		printf("type help voor meer informatie\n");
		break;
	case NO_SD_CARD_DETECTED:
		printf("er is geen SD kaart aanwezig, check SD kaart slot ");
		printf("type help voor meer informatie\n");
		break;
	case NO_COMMA_DETECTED:
		printf("er mist een , tussen de verschillende onderdelen van je message ");
		printf("type help voor meer informatie\n");
		break;
	case NO_END_TERMINATOR:
		printf("er mist een string terminator in je message ");
		printf("type help voor meer informatie\n");
		break;
	case HELP:
		printf("------------------------------HELP-----------------------\n");
		printf("\n");
		printf("Bericht layout's:\n");
		printf("tekst, x, y, kleur, tekst, fontnaam (arial, consolas), fontgrootte (1,2), fontstijl (normaal, vet, cursief)\n");
		printf("bitmap, nr, x-lup, y-lup  [tenminste: pijl (in 4 richtingen), smiley (boos, blij)]\n");
		printf("clearscherm, kleur\n");
		printf("wacht, msecs\n");
		printf("cirkel, x, y, radius, kleur\n");
		printf("rechthoek, x_lup, y_lup, breedte, hoogte, kleur, gevuld (1,0) [als 1: rand (1px) met kleur]\n");
		printf("lijn, x, y, x2, y2, kleur, dikte\n");
		printf("blur\n");
		printf("\n");
		printf("Parameters:\n");
		printf("Y max = 240\n");
		printf("X max = 320\n");
		printf("\n");
		printf("Voor meer info check de Handleiding\n");
		printf("------------------------------einde----------------------\n");
		break;
	default:
		printf("onbekende error");
		break;
	}
}

