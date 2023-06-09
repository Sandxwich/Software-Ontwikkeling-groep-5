/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EE_API
#define EE_API
/* Define to prevent usage in c++ errors -------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "fatfs.h"
#include "main.h"
#include "math.h"
#include "Arial.h"
#include "Arial_24.h"
#include "Consolas.h"
#include "consolas_24.h"
#include "API_error.h"

/* Defines -------------------------------------------------------------------*/
/*     |NAME                |  |Value|                                       */
#define ARIAL					1
#define CONSOLAS				2
#define SIZE_1					1
#define SIZE_2					2
#define THICKNESS				3
#define MAX_STYLE_LENGHT		7
#define SIZE_BITMAP				176
#define LETTER_SIZE_2_HEIGHT	48
#define LETTER_SIZE_1_HEIGHT	24
#define ASCII_START				32
#define BITMAPSIZE				60
#define NRBITMAPS				6

#define BITMAPSIZE	60
#define NRBITMAPS	6
#define PI			3.14159265359

/* Prototypes ----------------------------------------------------------------*/

//draw letter functions
int API_draw_text(uint16_t, uint16_t, uint8_t, char*, char*, uint8_t, char*);

uint16_t * draw_normal_letter(unsigned char,unsigned char, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t*);

uint16_t * draw_cursive_letter(unsigned char, unsigned char, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t*);

uint16_t * draw_fat_letter(unsigned char,unsigned char, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t*);

//one off functions
void API_err_handler();

int API_draw_line(uint16_t ,uint16_t, uint16_t, uint16_t, uint8_t, uint8_t);

int API_draw_bitmap(uint16_t, uint16_t, uint16_t);

int API_read_bitmap_SD(char*, uint16_t, uint16_t);

int API_clear_screen(uint8_t);

int API_draw_rectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t);

int API_draw_circle(uint16_t , uint16_t , uint16_t , uint8_t);

int API_blur_screen();

unsigned int API_wacht(uint16_t);

#ifdef __cplusplus
}
#endif
#endif /*EE_API */
