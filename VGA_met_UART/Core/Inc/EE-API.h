/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EE_API
#define EE_API
/* Define to prevent usage in c++ errors -------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "Arial.h"
#include "Consolas.h"
/* Defines -------------------------------------------------------------------*/
/*     |NAME                |  |Value|                                       */
#define ARIAL					1
#define CONSOLAS				2
#define SIZE_1					1
#define SIZE_2					2
#define MAX_STYLE_LENGHT		7
#define SIZE_BITMAP				176
#define LETTER_BITMAP_HEIGHT	48
#define BITMAPSIZE				60
#define NRBITMAPS				6

/* Prototypes ----------------------------------------------------------------*/
 uint16_t * draw_normal_letter(unsigned char,unsigned char, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t*);

//uint16_t * draw_cursive_letter(unsigned char, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t*);

uint16_t * draw_fat_letter(unsigned char,unsigned char, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t*);

int API_draw_text(uint16_t, uint16_t, uint8_t, char*, char*, uint8_t, char*);


int API_draw_line(uint16_t ,uint16_t, uint16_t, uint16_t, uint8_t, uint8_t);

int API_draw_bitmap(uint16_t, uint16_t, uint16_t);

int API_read_bitmap_SD(char*, uint16_t, uint16_t);

#ifdef __cplusplus
}
#endif
#endif /*EE_API */
