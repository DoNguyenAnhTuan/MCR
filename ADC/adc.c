
// File name	: adc.c
/*====================================*/
/*  Include                           */
/*====================================*/
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "../eeprom/eeprom.h"

/*====================================*/
/*	Global Variable Declaration       */
/*====================================*/
unsigned int v_black[8];
unsigned int v_white[8];
unsigned int v_compare[8];
unsigned int sensor_value[8];
unsigned char sensor;
unsigned int compareValue;
unsigned int minOfMaxSensorValue[8];
unsigned int maxOfMinSensorValue[8];
unsigned char isUpdate = 0;
/*====================================*/
/*  Function name: adc_init           */
/*  Parameter: null                   */
/*  Description: configure hardware   */
/*               for adc function     */
/*====================================*/
void adc_init(){

	// ADC initialization
	// ADC Clock frequency: 1000.000 kHz
	// ADC Voltage Reference: AVCC pin
	// Use 8-bit mode
	ADMUX=ADC_VREF_TYPE & 0xff;
	ADCSRA=0x84;
	compareValue = 300;
}

/*====================================*/
/*  Function name: read_adc           */
/*  Parameter: adc_input              */
/*  Return value: value of voltage    */
/*                after converting    */
/*  Description:1.return voltage level*/
/*               of adc_input led from*/
/*               sensor circuit       */
/*              2. AD converter       */
/*                  function          */
/*====================================*/
unsigned int read_adc(unsigned char adc_input)
{
	// Read the 8 most significant bits
	// of the AD conversion result
	ADMUX = adc_input | (ADC_VREF_TYPE & 0xff);
	// Delay needed for the stabilization of the ADC input voltage
	//_delay_us(10); 

	// Start the AD conversion
	ADCSRA|=0x40;

	// Wait for the AD conversion to complete
	while ((ADCSRA & 0x10)==0);

	ADCSRA|=0x10;
	return ADCW;
}
unsigned int read_bat(){
		// Read the 8 most significant bits
		// of the AD conversion result

		ADMUX = 0x00 | (ADC_VREF_TYPE & 0xff);
		 ADCSRB |= 0x08;
		// Delay needed for the stabilization of the ADC input voltage
		//_delay_us(10);

		// Start the AD conversion
		ADCSRA|=0x40;

		// Wait for the AD conversion to complete
		while ((ADCSRA & 0x10)==0);

		ADCSRA|=0x10;
		ADCSRB &= 0xf7;
		return ADCW;
}
/*====================================*/
/*  Function name: read_volt          */
/*  Parameter: null                   */
/*  Description: save value of voltage*/
/*               for 8 sensor on      */
/*               sensor circuit       */
/*====================================*/
void read_volt()
{
	unsigned char i = 0;
	for (i = 0; i < 8; i++)
	sensor_value[7-i] = read_adc(i);
}
/*====================================*/
/*  Function name: read_sensor        */
/*  Parameter: null                   */
/*  Description: update current value */
/*               on sensor circuit    */
/*               and output to led    */
/*====================================*/
void read_sensor(){
	unsigned char temp = 0;
	unsigned char i = 0;

	if(isUpdate == 0)
	{
		read_volt();
		for (i = 0; i < 8; i++)
		{
			temp = temp << 1;
			if (sensor_value[i] > v_compare[i])
			{
				temp |= 0x01;//0b00000001
			}
			else
			{
				temp &= 0xfe;//0b11111110
			}
		}
		sensor = temp;
	}
}
/*====================================*/
/*  Function name: save_sensor        */
/*  Parameter: color                  */
/*  Description: save value of voltage*/
/*              for 8 led on "color"  */
/*              line in eeprom of MCU.*/
/*				 color is BLACK       */
/*				or WHITE			  */
/*====================================*/
void save_sensor(unsigned char color)
{
	isUpdate = 0;
}
/*====================================*/
/*  Function name: update_vcompare    */
/*  Parameter: null                   */
/*  Description: update value of      */
/*               v_compare[8] and save*/
/*               in eeprom of MCU     */
/*====================================*/
void update_vcompare(){
	int i;
	for (i=0; i<8; i++)
	{
		v_compare[i] = (maxOfMinSensorValue[i] + minOfMaxSensorValue[i])/2;
	}
	eeprom_writestr(V_COMPARE_POS, v_compare, 16);
}

void update_white(){
	int i;
	for (i=0; i<8; i++)
	{
		minOfMaxSensorValue[i] = sensor_value[i];
	}
	for (i=0; i<8; i++)
	{
		v_compare[i] = (maxOfMinSensorValue[i] + minOfMaxSensorValue[i])/2;
	}
	
}
void update_black(){
	int i;
	for (i=0; i<8; i++)
	{
		maxOfMinSensorValue[i] = sensor_value[i];
	}
	for (i=0; i<8; i++)
	{
		v_compare[i] = (maxOfMinSensorValue[i] + minOfMaxSensorValue[i])/2;
	}
	
}
/*====================================*/
/*  Function name: read_vcompare      */
/*  Parameter: null                   */
/*  Description: read v_compare[8]    */
/*               from eeprom          */
/*====================================*/
void read_vcompare(){
	eeprom_readstr(V_COMPARE_POS, v_compare, 16);
}

/*====================================*/
/*  Function name: read_vcompare      */
/*  Parameter: null                   */
/*  Description: write v_compare[8]   */
/*               into eeprom          */
/*====================================*/
void write_vcompare(){
	/*eeprom_writestr(V_COMPARE_POS, v_compare, 8);*/
}


/****************END FILE**************/

