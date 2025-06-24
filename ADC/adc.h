
// File name	: adc.h


#ifndef	__ADC_H__
#define __ADC_H__

/*====================================*/
/* Constant setting           		  */
/*====================================*/
#define ADC_VREF_TYPE 		0x40 // 0100 0000: AVCC with external capacitor at AREF pin.
								 // left_adjust.
#define	WHITE	0
#define	BLACK	1

/*====================================*/
/* extern variable declaration		  */
/*====================================*/
extern unsigned char sensor;

/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
void adc_init();								// Configuration of hardware setting
unsigned int read_adc(unsigned char adc_input);
void read_sensor();								
void save_sensor(unsigned char color);
void lcd_putSensor(unsigned char color);
void update_vcompare();	
void update_white();
void update_black();						// update v_compare
unsigned int read_bat();
void read_vcompare();							// read v_compare form eeprom
void write_vcompare();							// write v_compare into eeprom

extern unsigned int sensor_value[8];
extern unsigned int minOfMaxSensorValue[8];
extern unsigned int maxOfMinSensorValue[8];
extern unsigned int compareValue;
#endif



/****************END FILE**************/

