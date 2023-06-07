#include "Logic_Layer.h"
#include "EE-API.h"







Message_parser LogicLayer_Parser(char *Message, unsigned int Messagelength)
{
	unsigned int i,j,k,l = 0;			// Maak iterators aan voor het maken van een moving window langs de buffer message
	i = 0;
	j = 0;
	k = 0;


	Message_parser localParser;

	  while (Message[i] != 0) 	// Kijk voor line end
	  {

		  while (Message[i] != 44 && Message[i] != 0)		//Detectie van de comma seperator
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
	  		localParser.Parser_Message[k][l] = Message[j];
	  		l++;
	  	  }

	  	  j = i+1;

	  	  if (Message[j] == 0x20)	// checking for spaces between lines
	  	  {
	  		  j++;
	  	  }

	  	  localParser.Parser_Message[k][l] = '\0';

	  	  i++;		//verhoog de iterator om niet in een oneindige loop te komen ivm while loop en komma detectie

	  	  k=(k+1);	//verhoog iterator voor meerdere berichten opslag

	  	  if (k > BUFFER_LEN) // Error detectie tegen oneindige while loop
	  	  	  {
	  		  	  printf("Error no message end detected \n");
	  		  	  break;
	  	  	  }

	  }

	localParser.Variable_length = k;

	return localParser;
}

int LogicLayer_CommandCheck(Message_parser *localParser)
{
	int i;
	unsigned char stringLength = sizeof(commands_check) / sizeof(commands_check[0]);
	unsigned char stringCheck = 0;
	unsigned char stringCorrect = 0;

	for (i = 1; i <= stringLength; i++)
	{
		stringCheck = strcmp(localParser->Parser_Message[0],commands_check[i-1]);
		if (stringCheck == 0)
		{
			stringCorrect = i;
		}
	}

	if (stringCorrect != 0)
	{
		return stringCorrect;
	}
	else return 0;

}

int LogicLayer_CommandSwitch(Message_parser *localParser, unsigned char Command)
{


	switch (Command)
	{
		case 1:	//lijn
		{
			if (localParser->Variable_length-1 == 6)
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

			break;
			}
			else return 0;
		}

		case 2:	//rechthoek
		{
			unsigned short x_lup,  y_lup,  breedte,  hoogte;
			unsigned char color, gevuld;


			x_lup = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[1]), 1);
			y_lup = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[2]), 2);
			breedte = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[3]), 3);
			hoogte = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[4]), 4);

			color = LogicLayer_ColourCheck(localParser, 5);
			gevuld = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[6]), 6);

			API_draw_rectangle(x_lup, y_lup, breedte, hoogte, color, gevuld);

			break;
		}

		case 3: //tekst
		{
			uint16_t x = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[1]), 1);
			uint16_t y = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[2]), 2);
			uint8_t kleur = LogicLayer_ColourCheck(localParser, 3);
			uint8_t fontgrootte = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[6]), 6);

			API_draw_text(x, y, kleur, localParser->Parser_Message[4],localParser->Parser_Message[5], fontgrootte, localParser->Parser_Message[7]);
			break;
		}

		case 4: //bitmap
		{
			unsigned short x_lup = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[2]), 2);
			unsigned short y_lup = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[3]), 3);
			API_read_bitmap_SD(localParser->Parser_Message[1], x_lup, y_lup);
			break;
		}

		case 5: //clearscherm
		{
			unsigned char color;
			color = LogicLayer_ColourCheck(localParser, 1);
			UB_VGA_FillScreen(color);
			break;
		}
		case 6:
		{
			unsigned int msecs = LogicLayer_intToAscii(localParser, strlen(localParser->Parser_Message[1]), 1);
			wacht(msecs);
			break;
		}
		case 9:
		{
			API_blur_screen();
			break;
		}
		default:
		{
			return 0;
		}
	}
	return 1;
}

int LogicLayer_ColourCheck(Message_parser* localParser, unsigned char StructLocation)
{
	int i;
	unsigned char stringLength = sizeof(message_col_string) / sizeof(message_col_string[0])+1;
	unsigned char stringCheck = 0;
	unsigned char stringCorrect = 0;

	for (i = 1; i < stringLength; i++)
	{
		stringCheck = strcmp(localParser->Parser_Message[StructLocation],message_col_string[i-1]);
		if (stringCheck == 0)
		{
			return stringCorrect = message_col[i-1];
		}
	}


	return 0;

}

unsigned int LogicLayer_intToAscii(Message_parser* localParser, int numbersize, int StructLocation)
{
	unsigned char i = 0;
	unsigned char DecimalshiftBuff = 0;
	unsigned int decimalvalue = 0;
	for (i = 0; i < numbersize; i++)
	{

			DecimalshiftBuff = localParser->Parser_Message[StructLocation][i];	// making sure array doesnt have a negative number
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

