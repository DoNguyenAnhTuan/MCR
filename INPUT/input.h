// File name	: input.h

#ifndef	__INPUT_H__
#define __INPUT_H__

/*====================================*/
/* Constant setting           		  */
/*====================================*/
#define BUTTON_PORT					PORTH
#define BUTTON_DIR					DDRH
#define DIPSW_PORT					PORTH
#define DIPSW_DIR					DDRH


#define KEY_MASK	0x0f
#define SW_MASK		0xf0


#define KEY0_PIN					PH0
#define KEY1_PIN					PH1
#define KEY2_PIN					PH2
#define KEY3_PIN					PH3

#define SW0_PIN						PH4
#define SW1_PIN						PH5
#define SW2_PIN						PH6
#define SW3_PIN						PH7


#define KEY0			0
#define KEY1			1
#define KEY2			2
#define KEY3			3
#define DSW0			4
#define DSW1			5
#define DSW2			6
#define DSW3			7

#define BUT1		get_key(KEY0)
#define BUT2		get_key(KEY1)
#define BUT3		get_key(KEY2)
#define BUT4		get_key(KEY3)
/*====================================*/
/* extern variable declaration		  */
/*====================================*/
extern unsigned char key_input;
extern unsigned char dipsw_input;
extern unsigned char gatesensorMaskut;

/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
void input_init();
void update_input();
unsigned char get_key(unsigned char _key_id);
unsigned char get_dipsw();
unsigned char get_extkey();
unsigned char getGateSensor();

#endif

/****************END FILE**************/

