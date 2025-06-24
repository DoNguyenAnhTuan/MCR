// File name	: beep.h
#ifndef	__BEEP_H__
#define	__BEEP_H__

/*====================================*/
/* Constant setting           		  */
/*====================================*/
#define BEEP_PORT	PORTB
#define BEEP_DDR	DDRB
#define BEEP_PIN	PB4

/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
void beep_init();					// configuration of hardware settings
void beep_mod();					// handle speakder on/off

void beep_on();						// speaker on function
void beep_off();					// speaker off function

void beep_long(unsigned int _timer);// speaker on during peirod _timer

#endif

/****************END FILE**************/

