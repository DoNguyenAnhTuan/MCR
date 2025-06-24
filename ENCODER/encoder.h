// File name	: encoder.h
#ifndef	__ENCODER_H__
#define __ENCODER_H__

#define ENC_COUNT_DIV	1 // nhan encoder moi (ENC_COUNT_DIV)xung (phai >0)

#include <avr/io.h>
#include <avr/interrupt.h>


extern volatile int distance1;
extern volatile int distance2;
extern unsigned char vel_now;
extern unsigned char vantoc;
void encoder_init();
void reset_distance();

#endif
