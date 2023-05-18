
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


//	switch (nr)
//	{
//
//	case 0:	// Pijl up
//	{
//		//doe iets met de bitmap
//		break;
//	}
//
//	case 1:	// Pijl down
//	{
//
//		break;
//	}
//
//	case 2:	// Pijl Left
//	{
//
//		break;
//	}
//
//	case 3: // Pijl Right
//	{
//
//		break;
//	}
//
//	case 4: // Smiley
//	{
//
//		break;
//	}
//
//	case 5: // Frowney
//	{
//
//		break;
//	}
//
//	}
	return error;
}

int API_read_bitmap_SD()
{
	FATFS FatFs;
    FIL fil; 		//File handle
    FRESULT fres; //Result after operations
    FRESULT rres;

    UINT i = 0;
    //uint8_t j = 0;

    fres = f_mount(&FatFs, "", 1); //1=mount now
    if (fres != FR_OK) {
   	printf("f_mount error (%i)\r\n", fres);
   	while(1);
    }


	fres = f_open(&fil, "test.txt", FA_READ);
	if (fres != FR_OK) {
	printf("f_open error (%i)\r\n",fres);
	while(1);
	}
	printf("I was able to open 'test.txt' for reading!\r\n");

	BYTE readBuf[30];
	i = 30;
	while (i == 30)
	{
	rres = f_read(&fil,(void*)readBuf, 30, &i);
	  if(rres == 0)
	  {
		printf("Read string from 'test.txt' contents: %s\r\n", readBuf);
	  }
	  else
	  {
		printf("f_gets error (%i)\r\n", fres);
	  }
	}
//	while (value != 3)
//	{
//		fres = f_read(&fil, readBuf, 1, &i);
//		test = f_tell(&fil);
//		value = atoi(readBuf);
//		printf("%d",value);
//		j++;
//	}


	f_close(&fil);

    f_mount(NULL, "", 0);

	return 0;
}
