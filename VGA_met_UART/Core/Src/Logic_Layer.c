/*
 * Logic_Layer.c
 * J.van Valkengoed, J. Riensema, Y. Henken
 *
 * 07/06/2023
 *
 * Version 1.
 *
 */
#include "Logic_Layer.h"
#include "EE-API.h"






/*****************************************************************************
 *
 * @brief Deze functie deelt de gegeven buffer op in hokjes om uit te kunnen lezen
 *
 * @param *PMessage dit variabel is het ontvangen bericht van de IO-laag
 * @param MessageLength dit variabel is de lengte van het ontvangen bericht
 *
 * @return deze functie returned de struct Message_parser hierin staan de verschillende variabelen opgedeeld in hokjes en het hoeveelheid ontvangen variabelen
 *
 *****************************************************************************/
Message_parser LogicLayer_Parser(char *PMessage, unsigned int Messagelength)
{
	unsigned int i,j,k,l = 0;			// Maak iterators aan voor het maken van een moving window langs de buffer message
	i = 0;
	j = 0;
	k = 0;


	Message_parser PlocalParser;

	  while (PMessage[i] != 0) 	// Kijk voor line end
	  {

		  while (PMessage[i] != 44 && PMessage[i] != 0)		//Detectie van de comma seperator
		  {
			  i++;

			  if (i > Messagelength) // Error detectie tegen oneindige while loop
			  {
				  printf("Error , not detected \n");
				  break;
			  }
		  }

	  	  for (l=0; j<i; j++)
	  	  {
	  		PlocalParser.Parser_Message[k][l] = PMessage[j];
	  		l++;
	  	  }

	  	  j = i+1;

	  	  if (PMessage[j] == 0x20)	// checking for spaces between lines
	  	  {
	  		  j++;
	  	  }

	  	  PlocalParser.Parser_Message[k][l] = '\0';

	  	  i++;		//verhoog de iterator om niet in een oneindige loop te komen ivm while loop en komma detectie

	  	  k=(k+1);	//verhoog iterator voor meerdere berichten opslag

	  	  if (k > BUFFER_LEN) // Error detectie tegen oneindige while loop
	  	  	  {
	  		  	  printf("Error no message end detected \n");
	  		  	  break;
	  	  	  }

	  }

	PlocalParser.Variable_length = k;

	return PlocalParser;
}

/*****************************************************************************
 *
 * @brief Deze functie kijkt naar welk command ontvangen is door de IO-laag
 *
 * @param *PlocalParser dit variabel is de struct die gereturned is door de Logiclayer_parser functie
 *
 * @return returned niks tenzij de commando niet gevonden is
 *
 *****************************************************************************/
int LogicLayer_CommandCheck(Message_parser* PlocalParser)
{
	int i;
	unsigned char stringLength = sizeof(commands_check) / sizeof(commands_check[0]);
	unsigned char stringCheck = 0;
	unsigned char stringCorrect = 0;

	for (i = 1; i <= stringLength; i++)
	{
		stringCheck = strcmp(PlocalParser->Parser_Message[0],commands_check[i-1]);
		if (stringCheck == 0)
		{
			stringCorrect = i;
		}
	}

	if (stringCorrect != 0)
	{
		return stringCorrect;
	}
	else API_err_handler(UNKNOWN_FUNCTION);
	return 0;
}

/*****************************************************************************
 *
 * @brief Deze functie kijkt naar welke commando ontvangen is, adhv de commando bepaalt het of er genoeg variabelen zijn en stopt het in de corresponderende commando
 *
 * @param *PlocalParser dit variabel is de struct die gereturned is door de Logiclayer_parser functie
 * @param Command dit is de commando die gevonden is in de functie LogicLayer_CommandCheck
 *
 * @return returned niks tenzij er niet genoeg variabelen mee zijn gegeven
 *
 *****************************************************************************/
int LogicLayer_CommandSwitch(Message_parser* PlocalParser, unsigned char Command)
{
	switch (Command)
	{
		case 1:	//lijn
		{
			if (PlocalParser->Variable_length-1 == 6)
			{
				unsigned short x_1, y_1, x_2, y_2;
				unsigned char dikte, color;

			x_1 = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[1]), 1);
			y_1 = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[2]), 2);
			x_2 = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[3]), 3);
			y_2 = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[4]), 4);
			color = LogicLayer_ColourCheck(localParser, 5);
			dikte = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[6]), 6);
			API_draw_line(x_1, y_1, x_2, y_2, dikte, color);
			return 0;
			break;
			}
			else API_err_handler(INVALID_MESSAGE);
		}

		case 2:	//rechthoek
		{
			if (PlocalParser->Variable_length-1 == 6)
			{
				unsigned short x_lup,  y_lup,  breedte,  hoogte;
				unsigned char color, gevuld;


				x_lup = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[1]), 1);
				y_lup = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[2]), 2);
				breedte = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[3]), 3);
				hoogte = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[4]), 4);

				color = LogicLayer_ColourCheck(PlocalParser, 5);
				gevuld = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[6]), 6);

				API_draw_rectangle(x_lup, y_lup, breedte, hoogte, color, gevuld);

				break;
			}
			else return 0;
		}

		case 3: //tekst
		{
			if (PlocalParser->Variable_length-1 == 7)
			{
				uint16_t x = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[1]), 1);
				uint16_t y = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[2]), 2);
				uint8_t kleur = LogicLayer_ColourCheck(PlocalParser, 3);
				uint8_t fontgrootte = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[6]), 6);

				API_draw_text(x, y, kleur, PlocalParser->Parser_Message[4],PlocalParser->Parser_Message[5], fontgrootte, PlocalParser->Parser_Message[7]);
				break;
			}
			else return 0;
		}

		case 4: //bitmap
		{

			if (PlocalParser->Variable_length-1 == 3)
			{
				unsigned short x_lup = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[2]), 2);
				unsigned short y_lup = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[3]), 3);

				API_read_bitmap_SD(PlocalParser->Parser_Message[1], x_lup, y_lup);
				break;
			}
			else return 0;
		}

		case 5: //clearscherm
		{
			if (PlocalParser->Variable_length-1 == 1)
			{
				unsigned char color;
				color = LogicLayer_ColourCheck(PlocalParser, 1);

				UB_VGA_FillScreen(color);

				break;
			}
		}

		case 6:
		{
			if (PlocalParser->Variable_length-1 == 1)
			{
				unsigned int msecs = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[1]), 1);

				wacht(msecs);

				break;
			}
			else return 0;
		}

		case 8:
		{
			if (PlocalParser->Variable_length-1 == 4)
			{
				uint16_t x_c = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[1]), 1);
				uint16_t y_c = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[2]), 2);
				uint16_t radius = LogicLayer_intToAscii(PlocalParser, strlen(PlocalParser->Parser_Message[3]), 3);
				uint8_t color = LogicLayer_ColourCheck(PlocalParser, 4);

				API_draw_circle(x_c, y_c, radius, color);

				break;
			}
			else return 0;
		}

		case 9:
		{
			if (PlocalParser->Variable_length-1 == 1)
			{
				API_blur_screen();

				break;
			}
			else return 0;
		}

		default:
		{
			API_err_handler(NO_ERROR)
			return 0;
		}
	}
	return NO_ERROR;
}

/*****************************************************************************
 *
 * @brief Deze functie kijkt naar welke kleur ontvangen is, dit geeft de kleur de corresponderende 8-bit kleur code
 *
 * @param *PlocalParser dit variabel is de struct die gereturned is door de Logiclayer_parser functie
 * @param StructLocation dit variabel geeft aan waar in de struct gewerkt moet worden
 *
 * @return returned nul tenzij de kleur niet is gevonden
 *
 *****************************************************************************/
int LogicLayer_ColourCheck(Message_parser* PlocalParser, unsigned char StructLocation)
{
	int i;
	unsigned char stringLength = sizeof(message_col_string) / sizeof(message_col_string[0])+1;
	unsigned char stringCheck = 0;
	unsigned char stringCorrect = 0;

	for (i = 1; i < stringLength; i++)
	{
		stringCheck = strcmp(PlocalParser->Parser_Message[StructLocation],message_col_string[i-1]);
		if (stringCheck == 0)
		{
			return stringCorrect = message_col[i-1];
		}
	}


	return 0;

}

/*****************************************************************************
 *
 * @brief Deze functie vertaald de string naar een decimale waarde
 *
 * @param *PlocalParser dit variabel is de struct die gereturned is door de Logiclayer_parser functie
 * @param StructLocation dit variabel geeft aan hoe groot de string is die vertaald moet worden
 * @param StructLocation dit variabel geeft aan waar in de struct gewerkt moet worden
 *
 * @return returned nul tenzij de gegeven waardes geen cijfer is
 *
 *****************************************************************************/
unsigned int LogicLayer_intToAscii(Message_parser* PlocalParser, int numbersize, int StructLocation)
{
	unsigned char i = 0;
	unsigned char DecimalshiftBuff = 0;
	unsigned int decimalvalue = 0;

	for (i = 0; i < numbersize; i++)
	{

		DecimalshiftBuff = PlocalParser->Parser_Message[StructLocation][i];	// making sure array doesnt have a negative number
		if (DecimalshiftBuff < '0' ||  DecimalshiftBuff > '9')
		{

		}
		else
		{
			DecimalshiftBuff -= '0';

			decimalvalue *= 10;
			decimalvalue += DecimalshiftBuff;
		}
	}
	return decimalvalue;
}

