/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include "speed.h"

/*====================================*/
/*  Function name: speed_init         */
/*  Parameter: null                   */
/*  Description: configure hardware   */
/*               for PWM (speed)      */
/*               function             */
/*====================================*/
void speed_init(){
	DIR_DDR  |=  _BV(DIR_LEFT)|_BV(DIR_RIGHT)|_BV(DIR_STEERING);
	PWM_DDR  |=  _BV(PWM_LEFT)|_BV(PWM_RIGHT)|_BV(PWM_STEERING);
	BRAKE_DDR  |=  _BV(BRAKE_RIGHT)|_BV(BRAKE_LEFT)|_BV(BRAKE_STEERING);
	BRAKE_POUT  |=  _BV(BRAKE_RIGHT)|_BV(BRAKE_LEFT)|_BV(BRAKE_STEERING);
	// Timer/Counter 3 initialization
	// Clock source: System Clock
	// Clock value: 250.000 kHz
	// Mode: Ph. correct PWM top=0x00FF
	// OC3A output: Non-Inv.
	// OC3B output: Non-Inv.
	// OC3C output: Non-Inv.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer3 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR3A=(1<<COM3A1) | (0<<COM3A0) | (1<<COM3B1) | (0<<COM3B0) | (1<<COM3C1) | (0<<COM3C0) | (0<<WGM31) | (1<<WGM30);
	TCCR3B=(0<<ICNC3) | (0<<ICES3) | (0<<WGM33) | (0<<WGM32) | (0<<CS32) | (1<<CS31) | (0<<CS30);
	TCNT3H=0x00;
	TCNT3L=0x00;
	ICR3H=0x00;
	ICR3L=0x00;
	OCR3AH=0x00;
	OCR3AL=0x00;
	OCR3BH=0x00;
	OCR3BL=0x00;
	OCR3CH=0x00;
	OCR3CL=0x00;

}

/*====================================*/
/*  Function name: set_left_dir       */
/*  Parameter: _dir                   */
/*  Description: setting direction for*/
/*             left motor             */
/*====================================*/
void set_left_dir(unsigned char _dir){
	if(_dir == FORWARD)
		DIR_POUT |= _BV(DIR_LEFT);
	else
		DIR_POUT &= ~_BV(DIR_LEFT);
}

/*====================================*/
/*  Function name: set_right_dir      */
/*  Parameter: _dir                   */
/*  Description: setting direction for*/
/*             right motor            */
/*====================================*/
void set_right_dir(unsigned char _dir){
	if(_dir == FORWARD)
		DIR_POUT |= _BV(DIR_RIGHT);
	else
		DIR_POUT &= ~_BV(DIR_RIGHT);
}

/*====================================*/
/*  Function name: speed              */
/*  Parameter:_left_speed,_right_speed*/
/*  Description: setting speed for    */
/*             left and right motor   */
/*====================================*/
void speed(int _right_speed , int _left_speed){

	if(_left_speed >= 0){
		set_left_dir(FORWARD);
	}else{
		_left_speed = -_left_speed;
		set_left_dir(BACKWARD);
	}
	if(_right_speed >= 0){
		set_right_dir(FORWARD);
	}else{
		_right_speed = -_right_speed;
		set_right_dir(BACKWARD);
	}

	if(_left_speed > MAX_SPEED)  _left_speed = MAX_SPEED;
	if(_left_speed < MIN_SPEED)  _left_speed = 0;
	
	if(_right_speed > MAX_SPEED)  _right_speed = MAX_SPEED;
	if(_right_speed < MIN_SPEED)  _right_speed = 0;

	LEFT_SPEED  = _left_speed;
	RIGHT_SPEED = _right_speed;
}


/****************END FILE**************/

