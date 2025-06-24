
// File name	: handle.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include "handle.h"
#include "../eeprom/eeprom.h"


/*====================================*/
/*  Function name: handle_init        */
/*  Parameter: null                   */
/*  Description: 1.configure hardware */
/*               for handle function  */
/*               2.Used for handle    */
/*                  Servo motor       */
/*====================================*/
unsigned int handle_center = 1500;
void handle_init(){

	DDRB  |=  _BV(PB5);

	// Timer/Counter 3 initialization
	// Clock source: System Clock
	// Clock value: 2000.000 kHz
	// Mode: Ph. & fr. cor. PWM top=ICR3
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
// 	TCCR3A=0xA8;
// 	TCCR3B=0x12;
// 	TCNT3H=0x00;
// 	TCNT3L=0x00;
// 	ICR3H=0x3E;
// 	ICR3L=0x80;
// 	OCR3AH=0x00;
// 	OCR3AL=0x00;
// 	OCR3BH=0x00;
// 	OCR3BL=0x00;
// 	OCR3CH=0x00;
// 	OCR3CL=0x00;
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 2000.000 kHz
// Mode: Ph. & fr. cor. PWM top=ICR1
// OC1A output: Non-Inverted PWM
// OC1B output: Disconnected
// OC1C output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 5 ms
// Output Pulse(s):
// OC1A Period: 5 ms Width: 1.5 ms
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x13;
ICR1L=0x88;
OCR1AH=0x05;
OCR1AL=0xDC;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;
}

/*====================================*/
/*  Function name: handle             */
/*  Parameter: _angle                 */
/*  Description: used to control Servo*/
/*               to turn to "_angle"  */
/*====================================*/
void handle(int _angle){
	RC_ANGLE = handle_center - HANDLE_STEP * _angle;
}
void handleMicro(int _angle){
	RC_ANGLE = handle_center - _angle;
}
void save_handle_center ()
{
	eeprom_writebyte (HANDLE_CENTER_POS, 	handle_center);			//low byte
	eeprom_writebyte (HANDLE_CENTER_POS+1, 	handle_center>>8);		//hight byte
}
void read_handle_center ()
{
	handle_center = eeprom_readbyte (HANDLE_CENTER_POS+1);
	handle_center <<= 8;
	handle_center = handle_center + eeprom_readbyte (HANDLE_CENTER_POS);
	if (handle_center < 700)
		handle_center = 1500;
	if (handle_center > 2300)
		handle_center = 1500;
}

/****************END FILE**************/

