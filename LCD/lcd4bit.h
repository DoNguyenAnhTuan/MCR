// File name	: lcd4bit.h

#ifndef __LCD4BIT_H
#define __LCD4BIT_H

#define LCD_DATA_PORT		PORTC
#define LCD_DATA_PIN		PINC
#define LCD_DATA_DIR		DDRC
#define LCD_ENABLE_PORT		PORTC
#define LCD_ENABLE_DIR		DDRC
#define LCD_RS_PORT         PORTC
#define LCD_RS_DIR			DDRC
#define LCD_RW_PORT			PORTC
#define LCD_RW_DIR			DDRC

#define LCD_EN				PC7
#define LCD_RS			    PC5
#define LCD_RW				PC6


volatile unsigned char lcd_flag;
volatile unsigned char lcd_buff, lcd_buff_data;
unsigned char send_data;

/*******************************************************************************
Noi Dung    :   Gui tin hieu Enable den LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
 void LCD_Enable(void);
 
 /*******************************************************************************
 Noi Dung    :   Gui tin hieu Disable den LCD.
 Tham Bien   :   Khong.
 Tra Ve      :   Khong.
 ********************************************************************************/
 void LCD_Disable(void);
 
 /*******************************************************************************
Noi Dung    :   Gui 4 bit du lieu den LCD.
Tham Bien   :   Data: 4 bit thap cua Data chua 4 bit du lieu can gui.
Tra Ve      :   Khong.
********************************************************************************/

 void LCD_Send4Bit( unsigned char  Data );
 
 /*******************************************************************************
Noi Dung    :   Gui 1 byte du lieu den LCD.
Tham Bien   :   command: byte du lieu can gui.
Tra Ve      :   Khong.
********************************************************************************/
 void LCD_SendCommand (unsigned char command );
 
 /*******************************************************************************
Noi Dung    :   Khoi tao LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
 void LCD_Init ( void );
 
 /*******************************************************************************
Noi Dung    :   Thiet lap vi tri con tro LCD.
Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 15.
                y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_Gotoxy(unsigned char  x, unsigned char  y);

 /*******************************************************************************
Noi Dung    :   Xoa noi dung hien thi tren LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_Clr(void);

 /*******************************************************************************
Noi Dung    :   Viet 1 ki tu len LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_PutChar ( unsigned char  Data );

 /*******************************************************************************
Noi Dung    :   Viet 1 chuoi ki tu len LCD.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_PutFloat ( float  floatData );
void LCD_PutD( unsigned char  Data );
void LCD_PutDec(unsigned int Data);
void LCD_PutTime ( int Data );
void LCD_SendData (unsigned char  Data );
void LCD_SendCommand(unsigned char Data);
void LCD_Puts (char *s);
void LCD_Puts_Slow (char *s);
void LCD_PutHex(unsigned char data);
#endif
//******************************KET THUC FILE******************************




