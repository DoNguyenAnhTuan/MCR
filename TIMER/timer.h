// File name	: timer.h
#ifndef	__TIMER_H__
#define __TIMER_H__

/*============================*/
/* Constant setting           */
/*============================*/
#define TIMER_DIV	1

/*============================*/
/* extern variable declaration*/
/*============================*/
extern unsigned char timer_flag;
              
extern unsigned int   cnt1;    
extern unsigned int   cnt2;
extern unsigned int   cnt3;
extern unsigned int   cnt4;
extern unsigned char  curveFlag;
extern unsigned int  brakeCurve;
extern unsigned int   velocity;

/*============================*/
/* Prototype declaration      */
/*============================*/
void timer_init();
void virtual_timer();

#endif

/****************END FILE**************/

