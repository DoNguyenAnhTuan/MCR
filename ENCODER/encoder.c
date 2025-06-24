// File name	: encoder.c
#include "../encoder/encoder.h"
#include "../led/led.h"
volatile signed int distance1;
volatile signed int distance2;
unsigned char vel_now;
unsigned char vantoc1;
unsigned char vantoc2;

void encoder_init()
{
// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
// INT3: On
// INT3 Mode: Falling Edge
// INT4: Off
// INT5: Off
// INT6: Off
// INT7: Off
EICRA=(1<<ISC31) | (0<<ISC30) | (1<<ISC21) | (0<<ISC20) | (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (1<<INT3) | (1<<INT2) | (0<<INT1) | (0<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (1<<INTF3) | (1<<INTF2) | (0<<INTF1) | (0<<INTF0);

	DDRD	&= 0xf3; // PD23 is input//0xf3 :11110011
	PORTE	|=  (_BV(PD2) | _BV(PD3)); //pull up


	distance1 = 0;
	vantoc1 =0;
	distance2 = 0;
	vantoc2 =0;
}

void reset_distance()
{
	distance1 = 0;
	distance2 = 0;
}

//External interrupt 6 service routine
ISR(INT2_vect)
{		
		distance1 ++;

}
//External interrupt 7 service routine
ISR(INT3_vect)
{

		distance2 ++;
}

