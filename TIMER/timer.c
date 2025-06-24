// File name	: timer.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/interrupt.h>
#include "timer.h"
#include "../ENCODER/encoder.h"


/*====================================*/
/*	Global Variable Declaration       */
/*====================================*/

unsigned int	cnt1;    
unsigned int	cnt2;
unsigned int	cnt3;
unsigned int	cnt4;
unsigned char  curveFlag;
unsigned int  brakeCurve;
unsigned int	velocity;

/*====================================*/
/*  Function name: timer_init         */
/*  Parameter: null                   */
/*  Description: configure hardware   */
/*               for timer function   */
/*====================================*/
void timer_init()
{	
	cnt1 = cnt2 = cnt3 = cnt4 = 0;

// TCCR2 = 0x03;
// TCNT2 = 0x05;	// configure register to have timer 1ms
// TIMSK|=0x40;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 250.000 kHz
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
// Timer Period: 1 ms
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=0x06;
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (1<<TOIE0);
}


/*====================================*/
/*  Function name: virtual_timer      */
/*  Parameter: null                   */
/*  Description: virtual timer        */
/*           virtual delay to use in  */
/*           algorithm                */ 
/*====================================*/
void virtual_timer(){
	cnt1 ++;
	cnt2 ++;
	cnt4 ++;
	if (curveFlag == 0)
	{
		cnt3++;
	}
	else if (curveFlag == 1)		
	{
		cnt3 = 0;
		brakeCurve--;	
		if (brakeCurve < 10)
		{
			brakeCurve = 10;
		}	
	}
	if (cnt3 > 300)
	{
		brakeCurve = 81;
	}

//////// use for encoder	
// 	if(cnt3 == 50)
// 	{
// 		velocity = distance2;
// 		cnt3 = 0;
// 		distance2 =  0;
// 	}
}


/****************END FILE**************/

