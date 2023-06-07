/*
 * Parser.h
 *
 *  Created on: 24 mei 2023
 *      Author: gebruiker
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#define VGA_COL_BLACK 0x00
#define VGA_COL_BLUE 0x03
#define VGA_COL_LIGHTBLUE 0x73
#define VGA_COL_GREEN 0x1C
#define VGA_COL_LIGHTGREEN 0x7D
#define VGA_COL_CYAN 0x1F
#define VGA_COL_LIGHTCYAN 0x7F
#define VGA_COL_RED 0xE0
#define VGA_COL_LIGHTRED 0xE5
#define VGA_COL_MAGENTA 0xE3
#define VGA_COL_LIGHTMAGENTA 0xEF
#define VGA_COL_BROWN 0x8C
#define VGA_COL_YELLOW 0xFC
#define VGA_COL_GRAY 0x6D
#define VGA_COL_WHITE 0xFF
#define VGA_COL_PINK 0xEE

#define SIZE_OF_COMMANDS 20

static char const commands_check[][SIZE_OF_COMMANDS] = {"lijn", "rechthoek", "tekst", "bitmap", "clearscherm", "wacht", "herhaal","cirkel","blur","help" };


static char const message_col_string[][SIZE_OF_COMMANDS] = {"zwart", "blauw", "lichtblauw", "groen", "lichtgroen", "cyaan", "lichtcyaan",
												"rood", "lichtrood", "magenta", "lichtmagenta", "bruin", "geel", "grijs", "wit"};

static unsigned char const message_col[SIZE_OF_COMMANDS] = {VGA_COL_BLACK, VGA_COL_BLUE, VGA_COL_LIGHTBLUE, VGA_COL_GREEN, VGA_COL_LIGHTGREEN, VGA_COL_CYAN, VGA_COL_LIGHTCYAN, VGA_COL_RED, VGA_COL_LIGHTRED, VGA_COL_MAGENTA, VGA_COL_LIGHTMAGENTA, VGA_COL_BROWN, VGA_COL_YELLOW, VGA_COL_GRAY, VGA_COL_WHITE};


#endif /* INC_PARSER_H_ */
