// File name	: beep.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include "beep.h"
#include "../TIMER/timer.h"

/*====================================*/
/*	Global Variable Declaration       */
/*====================================*/
unsigned int beep_cn;
unsigned char beep_flag;

/*====================================*/
/*  Function name: beep_init          */
/*  Parameter: null                   */
/*  Description: configure hardware   */
/*               for beep speaker     */
/*====================================*/
void beep_init(){
	BEEP_DDR |= _BV(BEEP_PIN);
	beep_cn = 0;
	beep_flag = 0;
}

/*====================================*/
/*  Function name: beep_mod           */
/*  Parameter: null                   */
/*  Description: control beep from	  */
/* 				speaker by using	  */
/*				beep_flag and beep_cn.*/
/*				 This function is	  */
/*				called by interrupt	  */
/* 				timer				  */
/*====================================*/
void beep_mod(){
	if(beep_flag){
		beep_cn--;
		if(beep_cn==0){
			beep_flag = 0;
			beep_off();
		}
	}
}

/*====================================*/
/*  Function name: beep_on            */
/*  Parameter: null                   */
/*  Description: speaker on          */
/*====================================*/
void beep_on(){
	BEEP_PORT |= _BV(BEEP_PIN);
}

/*====================================*/
/*  Function name: beep_off           */
/*  Parameter: null                   */
/*  Description: speaker off          */
/*====================================*/
void beep_off(){
	BEEP_PORT &= ~_BV(BEEP_PIN);
}

/*====================================*/
/*  Function name: beep_long          */
/*  Parameter: timer                  */
/*  Description: speaker on during    */
/*               "_timer"             */
/*====================================*/
void beep_long(unsigned int _timer){
	beep_cn = _timer/TIMER_DIV;
	beep_flag = 1;
	beep_on();
}


/****************END FILE**************/



