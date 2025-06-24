// File name	: lcd4bit.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include <util/delay.h>
#include "lcd4bit.h"

/*====================================*/
/*	Global Variable Declaration       */
/*====================================*/
volatile unsigned char lcd_flag;
unsigned char lcd_Data, send_address, lcd_pattern_1, lcd_pattern_2, Data_data, send_data;
volatile unsigned char lcd_buff, lcd_buff_data;

 /*******************************************************************************
Noi Dung    :   Gui tin hieu Enable den LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

 void LCD_Enable(void)
{
	LCD_ENABLE_PORT |= _BV(LCD_EN);
	 _delay_us(3);
	LCD_ENABLE_PORT &= ~_BV(LCD_EN);
	_delay_us(150);
}


 /*******************************************************************************
Noi Dung    :   Gui 4 bit du lieu den LCD.
Tham Bien   :   Data: 4 bit thap cua Data chua 4 bit du lieu can gui.
Tra Ve      :   Khong.
********************************************************************************/

 void LCD_Send4Bit( unsigned char  Data )
{
	unsigned char temp;
	temp = LCD_DATA_PORT & 0xf0;
	LCD_DATA_PORT = (temp | (Data & 0x0f));
}
 
 /*******************************************************************************
Noi Dung    :   Gui 1 byte du lieu den LCD.
Tham Bien   :   Data: byte du lieu can gui.
Tra Ve      :   Khong.
********************************************************************************/

 void LCD_SendData (unsigned char  Data )
{
	//LCD_RS_PORT &= ~(_BV(LCD_RS));

	LCD_Send4Bit(Data>>4);
	LCD_Enable();
	LCD_Send4Bit(Data);
	LCD_Enable();
}
void LCD_SendCommand(unsigned char Data)
{
	
	LCD_RS_PORT &=~(_BV(LCD_RS));
	LCD_Send4Bit(Data>>4);
	LCD_Enable();
	LCD_Send4Bit(Data);
	LCD_Enable();
	LCD_RS_PORT |=(_BV(LCD_RS));
}
 /*******************************************************************************
Noi Dung    :   Khoi tao LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
 void LCD_Init ( void )
{	

	LCD_DATA_DIR |= 0x0f;
	LCD_RS_DIR |= (_BV(LCD_EN)|(_BV(LCD_RS)));
	LCD_RW_DIR |= _BV(LCD_RW);
	LCD_DATA_PORT &= 0xf0;
	_delay_ms(20);
	LCD_RS_PORT &= ~(_BV(LCD_RS));
	_delay_ms(5);
	LCD_RW_PORT &= ~(_BV(LCD_RW));
	_delay_ms(5);
	LCD_SendCommand(0x03);
	_delay_ms(10);
	LCD_Enable();
	_delay_ms(10);
	LCD_Enable();
	_delay_ms(10);
	LCD_Enable();
	_delay_ms(10);
	LCD_SendCommand(0x02);
	_delay_ms(10);
	LCD_SendData(0x28);       // giao thuc 4 bit, hien thi 2 hang, ki tu 5
	_delay_ms(10);
	LCD_SendCommand( 0x0c);          // cho phep hien thi man hinh
	_delay_ms(10);
	LCD_SendCommand( 0x06);         // tang ID, khong dich khung hinh
	_delay_ms(10);
	LCD_Clr();
	LCD_Gotoxy(0,0);

}
 /*******************************************************************************
Noi Dung    :   Thiet lap vi tri con tro LCD.
Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 15.
                y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_Gotoxy(unsigned char  x, unsigned char  y)
{
		LCD_RS_PORT &=~(_BV(LCD_RS));
		  unsigned char  address;
		  if(!y)
		  address = (0x80+x);
		  else
		  address = (0xC0+x);
		  _delay_ms(3);
		  LCD_SendCommand(address);
		  _delay_ms(1);
		  
}

 /*******************************************************************************
Noi Dung    :   Xoa noi dung hien thi tren LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_Clr(void)
{
  LCD_SendCommand(0x01);
  _delay_ms(10);
}
 /*******************************************************************************
Noi Dung    :   Viet 1 ki tu len LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
 void LCD_PutChar ( unsigned char  Data )
{	
		LCD_SendData(Data);
}

void LCD_PutFloat ( float  floatData )
{		
		int Data;
		floatData *= 10;
		Data = (int)floatData;
		
		if (Data < 10)
		{
			LCD_PutChar(32);
			LCD_PutChar(32);
			LCD_PutChar('0');
			LCD_PutChar('.');
			LCD_PutD(((Data%1000)%100)%10);
			
			
		}
		else if (Data < 100)
		{
			LCD_PutChar(32);
			LCD_PutChar(32);
			LCD_PutD(((Data%1000)%100)/10);
			LCD_PutChar('.');
			LCD_PutD(((Data%1000)%100)%10);
			
			
		}
		else if (Data < 1000)
		{
			LCD_PutChar(32);
			LCD_PutD((Data%1000)/100);
			LCD_PutD(((Data%1000)%100)/10);
			LCD_PutChar('.');
			LCD_PutD(((Data%1000)%100)%10);
			
		}
		else
		{
			LCD_PutD(Data/1000);
			LCD_PutD((Data%1000)/100);
			LCD_PutD(((Data%1000)%100)/10);
			LCD_PutChar('.');
			LCD_PutD(((Data%1000)%100)%10);
			
		}
}

void LCD_PutDec(unsigned int Data)
{
	if (Data < 10)
	{
		LCD_PutD((((Data%10000)%1000)%100)%10);
		LCD_Puts("  ");
	}
	else if (Data < 100)
	{
			
		LCD_PutD(((Data%10000)%1000)%100/10);
		LCD_PutD((((Data%10000)%1000)%100)%10);
		LCD_Puts(" ");
	}
	else if (Data < 1000)
	{	
		LCD_PutD(((Data%10000)%1000)/100);
		LCD_PutD(((Data%10000)%1000)%100/10);
		LCD_PutD((((Data%10000)%1000)%100)%10);
//		LCD_Puts("  ");
	}
// 	else if (Data < 10000)
// 	{
// 		LCD_PutD((Data%10000)/1000);
// 		LCD_PutD(((Data%10000)%1000)/100);
// 		LCD_PutD(((Data%10000)%1000)%100/10);
// 		LCD_PutD((((Data%10000)%1000)%100)%10);
// 		LCD_PutChar(32);
// 	}
// 	else
// 	{
// 		LCD_PutD(Data/10000);
// 		LCD_PutD((Data%10000)/1000);
// 		LCD_PutD(((Data%10000)%1000)/100);
// 		LCD_PutD(((Data%10000)%1000)%100/10);
// 		LCD_PutD((((Data%10000)%1000)%100)%10);
// 	}		
	
}
void LCD_PutTime ( int Data )
{
	int hour, minute, second;
	second = Data;
	minute = second/60;
	hour = minute/60;
	if (second > 59)
	{
		second = second - (minute*60);
	}
	if (minute > 59)
	{
		minute = minute - (hour * 60);
	}
	LCD_PutD(((hour)%100/10));
	LCD_PutD((((hour)%100)%10));
	//LCD_PutDec(hour);
	LCD_PutChar(':');
	LCD_PutD(((minute)%100/10));
	LCD_PutD((((minute)%100)%10));
//	LCD_PutDec(minute);
	LCD_PutChar(':');
	LCD_PutD(((second)%100/10));
	LCD_PutD((((second)%100)%10));
//	LCD_PutDec(second);
}

void LCD_PutD ( unsigned char  Data )
{
	
	Data = Data + '0';
	LCD_PutChar(Data);	

}
 /*******************************************************************************
Noi Dung    :   Viet 1 chuoi ki tu len LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
// void LCD_Puts(char *s)
// {	
// 	while(*s)
// 	{
// 		LCD_PutChar(*s);
// 		s++;
// 	}
// }

void LCD_Puts(char *s)
{
	LCD_RS_PORT |= _BV(LCD_RS);
	while(*s)
	{
		LCD_SendData(*s);
		s=s+1;
	}
	LCD_RS_PORT &= ~_BV(LCD_RS);
}
void LCD_PutHex(unsigned char data){
	if ((data & 0b10000000) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b01000000) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b00100000) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b00010000) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b00001000) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b00000100) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b00000010) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");
	if ((data & 0b00000001) != 0x00) LCD_Puts("1");
	else LCD_Puts("0");

}