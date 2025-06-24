#ifndef _RUN_H_
#define _RUN_H_

#define         MASK2_2         0x66    /* xooxxoox                     */ 
#define         MASK2_0         0xc0    /* ooxxxxxx                     */
#define         MASK0_2         0x03    /* xxxxxxoo                     */
#define         MASK3_3         0xe7    /* oooxxooo                     */
#define         MASK0_3         0x07    /* xxxxxooo                     */
#define         MASK3_0         0xe0    /* oooxxxxx                     */
#define         MASK4_0         0xf0    /* ooooxxxx                     */
#define         MASK0_4         0x0f    /* xxxxoooo                     */
#define         MASK1_1         0x81    /* oxxxxxxo                     */
#define			MASK4_4			0xff	/* oooooooo						*/

#define HALF_RIGHT_LINE		1
#define HALF_LEFT_LINE		2
/*======================================*/
/* Prototype declaration                */
/*======================================*/
void run();
char checkCrossLine( void );
unsigned char sensorMask( unsigned char mask );
void handleAndSpeed (int angle,int speed);
char checkCrossHalfLine(void);
void runForwardLine (int speedRun);
void runForwardLine90 (int speedRun90);
void runForwardLineRight(int speedRun);
void runForwardLineLeft(int speedRun);
void brakeTheCar(int time,int speedRun);
int turn90(int speedRun);
int leftLaneChange (int speedRun);
int rightLaneChange(int speedRun);
void handleAndSpeedMicro (int angle,int speed1);

/*======================================*/
/* Global Variable Declaration          */
/*======================================*/
               
extern signed char sensorPos;
extern signed int line;


#endif
