
#ifndef __Logic_Layer_H
#define __Logic_Layer_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define BUFFER_LEN 20


 typedef struct
 {
 	unsigned char Variable_length; // Hoeveelheid array
 	char Parser_Message[BUFFER_LEN][BUFFER_LEN]; // 2d array voor het returnen van de message
 } Message_parser;

 extern Message_parser Debugging;

Message_parser LogicLayer_Parser(char*, unsigned int);


#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */
