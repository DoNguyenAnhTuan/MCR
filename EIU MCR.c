
#include "EIU MCR.h"

/*====================================*/
/*  interrupt timer0                  */
/*  Description: interrupt timer1 with*/
/*               cycle 1ms used to    */
/*               manage program       */
/*====================================*/
ISR (TIMER0_OVF_vect)
{
	// Reinitialize Timer 1 value
	TCNT0 = 0x06;
	
	virtual_timer();
	beep_mod();
	update_input();
	read_sensor();
	led_put(sensor);
}
/*====================================*/
/*  Function name: main               */
/*  Description: 1. main function     */
/*               2. Initialize system */
/*               3. Run application  */
/*====================================*/
int main()
{
	init();         // initialize system
	asm("sei");		// global interrupt enable
	speed(0,0);
	testing_flag = 1;
	beep_long(20);	// speaker on during 20ms
	LCD_Gotoxy(3,0);
	LCD_Puts("EIU MCR");
	LCD_Gotoxy(2,1);
	LCD_Puts("EIU.EDU.VN");
	_delay_ms(1500);
	LCD_Clr();
	batteryCheck();// if low battery the beep is on, battery must be charge
	test();
	run();
	return 1;
}

/*====================================*/
/*  Function name: init               */
/*  Description: 1. Configure hardware*/
/*               2. Initialize system */
/*====================================*/
void init()
{
	atmega2560_init();
	handle_init();
	speed_init();
	timer_init();
	adc_init();
	beep_init();
	led_init();
	input_init();
	encoder_init();
	read_handle_center ();
	handle(0);
	read_vcompare();	//read v_compare values form eeprom
	LCD_Init();
}
void batteryCheck()
{
	int volt = read_bat()*100/342;
	LCD_Gotoxy(3,0);
	LCD_PutDec(volt);
	while(read_bat()<300){
		beep_long(20);
		_delay_ms(100);
	}
}
/*====================================*/
/*  Function name: atmega64_init      */
/*  Description: initial configuration*/
/*              for ATmega64 MCU      */
/*====================================*/
void atmega2560_init(){
	// Turn Off Analog Comparator: Off
	ACSR=0x80;
}


/****************END FILE**************/