

/*====================================*/
/*  Include                           */
/*====================================*/
#include <util/delay.h>
#include "test.h"
#include "../ADC/adc.h"
#include "../BEEP/beep.h"
#include "../LED/led.h"
#include "../HANDLE//handle.h"
#include "../SPEED/speed.h"
#include "../INPUT/input.h"
#include "../TIMER/timer.h"
#include "../ENCODER/encoder.h"
//#include "../UART/uart.h"
#include "../RUN/run.h"
#include "../LCD/lcd4bit.h"

volatile unsigned char testing_flag = 1;
/*====================================*/
/*  Function name: test               */
/*  Parameter: null                   */
/*  Description: to implement cases   */
/*              to test all modules   */
/*              on the car       */
/*====================================*/

void test(){
	while(testing_flag == 1){
		switch(get_dipsw()){
			case 0:
			RGB(1,0,0); //the RGB light turns red
			/*************line sensor calibration************/
			if (SW1){	// press SW1 to update black value
				update_black();
				beep_long(20);
			}
			if (SW2){	// press SW2 to update white value
				update_white();
				beep_long(100);
			}
			if (SW3){	// press SW3 to save sensor value
				update_vcompare();
				beep_long(300);
			}
			if (SW4){	// press SW4 to save sensor value
				update_vcompare();
				beep_long(300);
			}
			break;
			case 1:
			RGB(0,1,0);//the RGB light turns green
			/************test DC motor***********/
			if (SW2){			// press KEY1 to run left motor  backward
				speed(-250,0);
				_delay_ms(10);
				}else if(SW1){		// press KEY0 to run left motor forward
				speed(250,0);
				_delay_ms(10);
				}else if(SW4){		// press KEY3 to run right motor backward
				speed(0,-250);
				_delay_ms(10);
				}else if(SW3){		// press KEY2 to run right motor forward
				speed(0, 250);
				_delay_ms(10);
				}else{				// stop
				speed(0,0);
			}
			
			break;
			case 2:
			RGB(0,0,1);//the RGB light turns blue
			/************test RC servo***********/
			if (SW3){			// press SW3 to turn right
				handle_center -= 2;
				handle(0);
				_delay_ms(50);
				}else if(SW2){	// press SW2 to turn left
				handle_center += 2;
				handle(0);
				_delay_ms(50);
			}
			else if (SW1||SW4)
			{
				save_handle_center();
				_delay_ms(1000);
				beep_long(200);
				_delay_ms(200);
			}
			break;
			case 3://test encoder
			RGB(1,1,0);//the RGB light turns yellow
			LCD_Gotoxy(0,0);
			LCD_PutDec(distance1);
			/************test Encoder***********/
			break;
			case 4://the RGB light turns blue
			RGB(0,1,1);
			LCD_Clr();
			LCD_Gotoxy(0,0);
			LCD_PutDec(sensor_value[7]);
			LCD_Gotoxy(4,0);
			LCD_PutDec(sensor_value[6]);
			LCD_Gotoxy(8,0);
			LCD_PutDec(sensor_value[5]);
			LCD_Gotoxy(12,0);
			LCD_PutDec(sensor_value[4]);
			LCD_Gotoxy(0,1);
			LCD_PutDec(sensor_value[3]);
			LCD_Gotoxy(4,1);
			LCD_PutDec(sensor_value[2]);
			LCD_Gotoxy(8,1);
			LCD_PutDec(sensor_value[1]);
			LCD_Gotoxy(12,1);
			LCD_PutDec(sensor_value[0]);
			_delay_ms(100);
			//RYGB(0,100,0,0);
			break;
			case 5:
			RGB(1,0,1);//the RGB light turns purple
			if (SW3){			// press SW3 to turn right
				
				handle(35);
				_delay_ms(50);
				}else if(SW2){	// press SW2 to turn left
				
				handle(-35);
				_delay_ms(45);
			}
			
			break;
			default:// go to run.c
			RGB(0,0,0);
			if (SW1)
			{
				
				testing_flag = 0;
				beep_long(200);
			}
			else if(SW4)
			{
				testing_flag = 0;
				beep_long(200);
			}
			else if (SW2)
			{
				
				testing_flag = 0;
				beep_long(200);
			}
			else if(SW3)
			{
				testing_flag = 0;
				beep_long(200);
			}
			
			break;
			
		}
	}
}

/****************END FILE**************/

