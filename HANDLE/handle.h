// File name	: handle.h

#ifndef	__HANDLE_H__
#define __HANDLE_H__

/*====================================*/
/* Constant setting           		  */
/*====================================*/
#define RC_ANGLE		OCR1A
#define HANDLE_STEP		10

/*====================================*/
/* Prototype declaration      		  */
/*====================================*/
extern unsigned int handle_center;
void save_handle_center ();
void read_handle_center ();
void handle_init();
void handle(int _angle);
void handleMicro(int _angle);
#endif

/****************END FILE**************/

