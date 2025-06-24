// File name	: eeprom.h
#ifndef __EEPROM_H__
#define __EEPROM_H__

/*====================================*/
/* Constant setting           		  */
/*====================================*/
#define DISABLE_INT  	0x7F
#define ENABLE_INT	 	0x80
#define V_WHITE_POS		8
#define V_BLACK_POS		16
#define V_COMPARE_POS	24
#define HANDLE_CENTER_POS 40

/*====================================*/
/* Prototype declaration        	  */
/*====================================*/
void eeprom_init();
void eeprom_writebyte(	unsigned char uiAddress, 
					  	unsigned char data);
void eeprom_writestr(	unsigned char uiAddress_start, 
					 	unsigned char *ucData_buff, 
						unsigned char ucData_len);

unsigned char eeprom_readbyte(unsigned char uiAddress);
void eeprom_readstr(	unsigned char uiAddress_start, 
						unsigned char *ucData_buff, 
						unsigned char ucData_len);

#endif

/****************END FILE**************/

