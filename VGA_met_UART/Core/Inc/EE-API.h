/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EE_API
#define EE_API
/* Define to prevent usage in c++ errors -------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "Bitmap.h"

#include "fatfs.h"

/* Defines -------------------------------------------------------------------*/

#define BITMAPSIZE	60
#define NRBITMAPS	6

/* Prototypes ----------------------------------------------------------------*/
int API_draw_line(uint16_t ,uint16_t, uint16_t, uint16_t, uint8_t, uint8_t);

int API_draw_bitmap(uint16_t, uint16_t, uint16_t);

int API_read_bitmap_SD(char*, uint16_t, uint16_t);

int API_draw_rectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t);

#ifdef __cplusplus
}
#endif
#endif /*EE_API */
