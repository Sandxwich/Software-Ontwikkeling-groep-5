/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef API_ERR
#define API_ERR
/* Define to prevent usage in c++ errors -------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif
/*global error variable ------------------------------------------------------*/
 static unsigned char API_err_code = 0x00;
/*ERROR codes ----------------------------------------------------------------*/
#define NO_ERROR				0x00 //geen errors
#define	INVALID_MESSAGE			0x01 //mist input variables
#define X_OUT_OF_BOUNDS			0x02 //X waarde hoger dan 320
#define Y_OUT_OF_BOUNDS			0X03 //Y waarde hoger dan 240
#define NOT_A_NUMBER			0x04 //input moet een getal zijn. huidige input is dat niet
#define NOT_A_CHARACTER			0x05 //input moet een character zijn. huidige input is dat niet
#define UNKNOWN_COLOR			0X06 //kleur gegeven is niet bekend
#define UNKNOWN_BITMAP			0x07 //bitmap nr bestaat niet in de huidige bitmaps
#define UNKNOWN_FONT			0x08 //ingevulde font bestaat niet
#define UNKNOWN_FONT_SIZE		0x09 //ingevulde font grote is niet bekend
#define UNKNOWN_FONT_STYLE		0x0A //ingevulde font stijl is niet bekend
#define UNKNOWN_FUNCTION		0x0B //opgegeven functie niet bekend
#define Y_TO_HIGH				0X0C //figuur dat getekent word zal buiten de y-as van het scherm belanden
#define X_TO_HIGH				0X0D //figuur dat getekent word zal buiten de x-as van het scherm belanden
#define NO_SD_CARD_DETECTED		0x0E //er is geen SD kaart gevonden. check SD slot
#define	NO_COMMA_DETECTED		0x10 //er zijn , nodig om de variabelen uit elkaar te halen. deze is nu niet aanwezig
#define	NOT_VALID_CHAR			0x11 //de char die in de zin staat, staat niet in de mogelijke char'ss

#ifdef __cplusplus
}
#endif
#endif /*ERROR */
