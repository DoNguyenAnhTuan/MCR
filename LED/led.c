// File name	: led.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include "led.h"



/*====================================*/
/*  Function name: led_init           */
/*  Parameter: null                   */
/*  Description: configure hardware   */
/*               for led function     */
/*====================================*/
void led_init(){
	LED_DATA_DIR = 0xFF;
	LED_DATA_PORT = 0xff;
	GRB_DATA_DIR |= 0x38;
	GRB_DATA_PORT &= 0xc7;
}

/*====================================*/
/*  Function name: led_put            */
/*  Parameter: _val                   */
/*  Description: output _val into led */
/*             module on MCU circuit  */
/*====================================*/
void led_put(unsigned char _val){
	LED_DATA_PORT = ~_val;
}


void RGB(unsigned char redColor,unsigned char greenColor,unsigned char blueColor){
	if (redColor > 0 )
	GRB_DATA_PORT |= 0b00010000;
	else GRB_DATA_PORT &= 0b11101111;
	if (greenColor > 0 )
	GRB_DATA_PORT |= 0b00100000;
	else GRB_DATA_PORT &= 0b11011111;
	if (blueColor > 0 )
	GRB_DATA_PORT |= 0b00001000;
	else GRB_DATA_PORT &= 0b11110111;
}

/****************END FILE**************/

