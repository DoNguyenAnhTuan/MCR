
#ifndef	__SPEED_H__
#define __SPEED_H__

/*====================================*/
/* Constant setting           		  */
/*====================================*/
#define	LEFT_SPEED		OCR3A
#define RIGHT_SPEED		OCR3B
#define STEERING		OCR3C

#define PWM_POUT		PORTE
#define PWM_PIN			PINE
#define PWM_DDR			DDRE
#define PWM_RIGHT		PE4
#define PWM_LEFT		PE3
#define PWM_STEERING	PE5

#define DIR_POUT		PORTE
#define DIR_PIN			PINE
#define DIR_DDR			DDRE
#define DIR_LEFT		PE2
#define DIR_RIGHT		PE6
#define DIR_STEERING	PE7

#define BRAKE_POUT		    PORTB
#define BRAKE_PIN			PINB
#define BRAKE_DDR			DDRB
#define BRAKE_LEFT			PB0
#define BRAKE_RIGHT			PB1
#define BRAKE_STEERING		PB2

#define BACKWARD		0
#define FORWARD			1

#define MAX_SPEED		255
#define MIN_SPEED		0

/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
void speed_init();

void set_left_dir(unsigned char _dir);
void set_right_dir(unsigned char _dir);

void speed(int _left_speed, int _right_speed);

#endif



/****************END FILE**************/

