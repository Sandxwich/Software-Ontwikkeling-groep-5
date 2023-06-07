#include "Logic_Layer.h"
#include "main.h"



Message_parser LogicLayer_Parser(char*, unsigned int);

/**********************************************************************//**
@brief This function serves as a parser for the project

@param Message
@param MessageLength


@return Returns a parser
@return Returns an error if error or returns nothing


 *************************************************************************/

Message_parser LogicLayer_Parser(char *Message, unsigned int Messagelength)
{
	unsigned int i,j,k,l = 0;			// Maak iterators aan voor het maken van een moving window langs de buffer message

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
