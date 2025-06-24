// File name	: led.h


#ifndef	__LED_H__
#define	__LED_H__

#define LED_DATA_PORT		PORTA
#define LED_DATA_DIR		DDRA
#define GRB_DATA_PORT		PORTL
#define GRB_DATA_DIR		DDRL
// #define LED_GREEN		OCR5A
// #define LED_BLUE		OCR5B
// #define LED_RED			OCR5C
#define LED_GREEN_PIN	PL4
#define LED_BLUE_PIN	PL5
#define LED_RED_PIN		PL3
/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
void led_init();
void led_put(unsigned char _val);
void RGB(unsigned char redColor,unsigned char greenColor,unsigned char blueColor);
#endif


/****************END FILE**************/

