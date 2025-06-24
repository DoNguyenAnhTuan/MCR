

#ifndef EIU_MCR_H_
#define EIU_MCR_H_

/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ADC/adc.h"
#include "BEEP/beep.h"
#include "EEPROM/eeprom.h"
#include "LED/led.h"
#include "HANDLE//handle.h"
#include "SPEED/speed.h"
#include "INPUT/input.h"
#include "TIMER/timer.h"
#include "TEST/test.h"
#include "RUN/run.h"
#include "ENCODER/encoder.h"
#include "LCD/lcd4bit.h"

/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
void atmega2560_init();
void init();
void batteryCheck();

#endif 

/****************END FILE**************/