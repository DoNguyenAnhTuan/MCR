// File name	: eeprom.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include <stdlib.h>
#include "eeprom.h"
#include "avr/iom2560.h"

/*====================================*/
/*  Funciton name: eeprom_init        */
/*  Description : initialize eeprom   */
/*                 funciton           */
/*====================================*/
void eeprom_init(){
	//nothing to init when using EEPROM
}

/*====================================*/
/*  Funciton name: eeprom_writebyte   */
/*  Parameter: uiAddress,ucData       */
/*  Description : write ucData into   */
/*              eeprom at uiAddress   */
/*====================================*/
void eeprom_writebyte(unsigned char uiAddress, unsigned char ucData){
	while(EECR & _BV(EEPE)); 	//Wait for completion of previous write
	EEAR = uiAddress;			//Set up address and data registers
	EEDR = ucData;
	SREG = SREG & DISABLE_INT;			//disable interrup

	asm volatile("sbi %0,%1" :: "I" (_SFR_IO_ADDR(EECR)) , "I" (2));
	asm volatile("sbi %0,%1" :: "I" (_SFR_IO_ADDR(EECR)) , "I" (1));

	SREG = SREG | ENABLE_INT;			//re-enable interrupt
}

/*====================================*/
/*  Funciton name: eeprom_writestr    */
/*  Parameter: uiAddress_start,       */
/*          *ucData_buff, ucData_len  */
/*  Description : write string from   */
/*           *ucData_buff with length */
/*           is "len" into eeprom     */
/*           from uiAddress_start     */
/*====================================*/
void eeprom_writestr(unsigned char uiAddress_start, unsigned char *ucData_buff, unsigned char ucData_len){
	unsigned char i__;
	if(!ucData_buff)return;
	for(i__=0;i__<ucData_len;i__++){
		eeprom_writebyte(uiAddress_start + i__, ucData_buff[i__]);
	}
}

/*====================================*/
/*  Funciton name: eeprom_readbyte    */
/*  Parameter: uiAddress,ucData       */
/*  Description : read ucData form    */
/*              eeprom at uiAddress   */
/*====================================*/
unsigned char eeprom_readbyte(unsigned char uiAddress){
	while(EECR & _BV(EEPE)); 	//Wait for completion of previous write
	SREG = SREG & 0x7f;			//disable interrup
	EEAR = uiAddress;			//Set up address register
	EECR |= _BV(EERE);			//Start eeprom read by writing EERE
	SREG = SREG | 0x80;			//re-enable interrupt
	return EEDR;				//Return data from data register
}

/*====================================*/
/*  Funciton name: eeprom_readstr     */
/*  Parameter: uiAddress_start,       */
/*          *ucData_buff, ucData_len  */
/*  Description : read string from    */
/*           *ucData_buff with length */
/*           is "len" from eeprom     */
/*           at uiAddress_start       */
/*====================================*/
void eeprom_readstr(unsigned char uiAddress_start, unsigned char *ucData_buff, unsigned char ucData_len){
	unsigned char i__;
	if(!ucData_buff)
		ucData_buff = malloc(ucData_len);
	if(!ucData_buff)return;
	for(i__=0;i__<ucData_len;i__++){
		*ucData_buff++ = eeprom_readbyte(uiAddress_start + i__);
	}
}


/****************END FILE**************/




