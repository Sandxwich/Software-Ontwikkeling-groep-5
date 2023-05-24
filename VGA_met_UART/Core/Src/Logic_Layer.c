#include "Logic_Layer.h"





Message_parser LogicLayer_Parser(char*, unsigned int);

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

int LogicLayer_CommandCheck(Message_parser localParser)
{
	int i;
	unsigned char stringLength = sizeof(commands_check) / sizeof(commands_check[0]);
	unsigned char stringCheck = 0;
	unsigned char stringCorrect = 0;

	for (i = 1; i < stringLength; i++)
	{
		stringCheck = strcmp(localParser.Parser_Message[0],commands_check[i-1]);
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

int LogicLayer_CommandSwitch(unsigned char Command, Message_parser localParser)
{

	switch (Command)
	{
		case 1:	//lijn
		{
			unsigned short x_1, y_1, x_2, y_2;
			unsigned char dikte, color;

			x_1 = intToAscii(&localParser, strlen(localParser.Parser_Message[1]), 1);
			y_1 = intToAscii(&localParser, strlen(localParser.Parser_Message[2]), 2);
			x_2 = intToAscii(&localParser, strlen(localParser.Parser_Message[3]), 3);
			y_2 = intToAscii(&localParser, strlen(localParser.Parser_Message[4]), 4);
			dikte = intToAscii(&localParser, strlen(localParser.Parser_Message[6]), 6);

			color = LogicLayer_ColourCheck(&localParser, 5);

			API_draw_line(x_1, y_1, x_2, y_2, dikte, color);

			break;
		}

		case 2:	//rechthoek
		{

			break;
		}

		case 3: //tekst
		{

			break;
		}

		case 4: //bitmap
		{
			unsigned short x_lup = intToAscii(&localParser, strlen(localParser.Parser_Message[2]), 2);
			unsigned short y_lup = intToAscii(&localParser, strlen(localParser.Parser_Message[3]), 3);
			API_read_bitmap_SD(localParser.Parser_Message[1], x_lup, y_lup);
			break;
		}

		case 5: //clearscherm
		{



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

