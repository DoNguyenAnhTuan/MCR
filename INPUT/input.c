// File name	: input.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include "input.h"

/*====================================*/
/*	Global Variable Declaration       */
/*====================================*/
unsigned char key1, key2, key0, key_input;
unsigned char dipsw1, dipsw2, dipsw0, dipsw_input;
unsigned char gatesensor1, gatesensor2, gatesensor0, gatesensorMaskut;

/*====================================*/
/*  Function name: input_init         */
/*  Parameter: null                   */
/*  Description:1. Configure hardware */
/*               for input function   */
/*              2. Dipswitch, push    */
/*                 button             */
/*====================================*/
void input_init(){
	BUTTON_DIR  &= ~(_BV(KEY0_PIN) | _BV(KEY1_PIN) | _BV(KEY2_PIN) | _BV(KEY3_PIN));
	BUTTON_PORT |= _BV(KEY0_PIN) | _BV(KEY1_PIN) | _BV(KEY2_PIN) | _BV(KEY3_PIN);			// 4 push button on MCU Circuit
	DIPSW_DIR  &= ~(_BV(SW0_PIN) | _BV(SW1_PIN) | _BV(SW2_PIN) | _BV(SW3_PIN));
	DIPSW_PORT |= _BV(SW0_PIN) | _BV(SW1_PIN) | _BV(SW2_PIN) | _BV(SW3_PIN);				// dip switch 4 on MCU Circuit
//	DDRD &= ~(_BV(GATE_SENSOR_PIN) | _BV(CONGTACCAU_PIN));
//	PORTD |= _BV(GATE_SENSOR_PIN) | _BV(CONGTACCAU_PIN);
	
	//PORTE |= _BV(PE2);		// push button on "capacity" circuit
	//DDRE  &= ~_BV(PE2);
//	DDRE  &= ~_BV(GATE_SENSOR_PIN);
//	PORTE |= _BV(GATE_SENSOR_PIN);		// sensor to recognize gate
	

	key1 = key2 = key0 = key_input = 0x0f;
	dipsw1 = dipsw2 = dipsw0 = dipsw_input = 0xf0;
}

/*====================================*/
/*  Function name: update_input       */
/*  Parameter: null                   */
/*  Description:update input value    */
/*             from dip switch and push*/
/*             button                 */
/*====================================*/
void update_input(){
	unsigned char _temp;

	key2 = key1;
	key1 = key0;
	dipsw2  = dipsw1;
	dipsw1  = dipsw0;

	_temp = PINH;
	dipsw0  = _temp & SW_MASK;
	key0 = _temp & KEY_MASK;

	if((dipsw0==dipsw1)&&(dipsw1==dipsw2))
		dipsw_input = dipsw0;

  	if ((key0 == key1) && (key1 == key2)){
		key_input = key0;
	}

// 	gatesensor2 = gatesensor1;
// 	gatesensor1 = gatesensor0;
// 	if((PIND & 0x01)!= 0) gatesensor0 = 1;
// 	else gatesensor0 = 0;
// 	gatesensorMaskut = gatesensor0;
}

/*====================================*/
/*  Function name: get_key            */
/*  Parameter: _key_id                */
/*  Return value: unsigned char       */
/*  Description: get state of push    */
/*         button on MCU circuit      */
/*		   _key_id is KEY0, KEY1, KEY2*/
/*			or KEY3					  */
/*====================================*/
unsigned char get_key(unsigned char _key_id){
	if(key_input & _BV(_key_id))
		return 0;
	return 1;
}

/*====================================*/
/*  Function name: get_dipsw          */
/*  Parameter: null                   */
/*  Return value: unsigned char       */
/*  Description: get state of         */
/*                          dipswitch */
/*====================================*/
unsigned char get_dipsw(){
	return (dipsw_input>>4);
}

/*====================================*/
/*  Function name: getGateSensor     */
/*  Parameter: null                   */
/*  Return value: unsigned char       */
/*  Description: get state of  gate   */
/*               sensor               */
/*====================================*/
unsigned char getGateSensor(){
	
	return gatesensorMaskut;
}


/****************END FILE**************/

