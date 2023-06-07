
#ifndef __Logic_Layer_H
#define __Logic_Layer_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "string.h"
#include "Parser.h"
#include "stdio.h"
//#include "EE-API.h"




#define BUFFER_LEN_PARSER 50
#define ARGUMENTEN_LEN 20
#define CIRCULAIR_BUFFER 10




 typedef struct
 {
 	unsigned char Variable_length; // Hoeveelheid array
 	char Parser_Message[ARGUMENTEN_LEN][BUFFER_LEN_PARSER]; // 2d array voor het returnen van de message
 } Message_parser;

 extern Message_parser Debugging;






Message_parser LogicLayer_Parser(char*, unsigned int);

int LogicLayer_CommandCheck(Message_parser*);

int LogicLayer_CommandSwitch(Message_parser* , unsigned char);

int LogicLayer_ColourCheck(Message_parser*, unsigned char);

unsigned int LogicLayer_intToAscii(Message_parser*, int , int );

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */
