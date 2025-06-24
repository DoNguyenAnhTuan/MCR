#include "motors.h"
#include "buzzer.h"
#include "led.h"
#include "pushButton.h"
#include "lineSensor.h"
#include "robot.h"

/* Motor control pins */
#define DIR1 2
#define PWM1 3
#define DIR3 4 
#define PWM3 5


/* Buzzer pin */
#define SPK 9 

/* LED pin */
#define LED 13

/* RC Servo pin */
#define SERVO 6


/* Button pins */
#define SW1 7
#define SW2 8
#define SW3 12

/* I2C_LCD/Ultrasonics sensor pins */
#define ECHO 10
#define TRIG 11 


/* Sensor pins of the robot: each pins has attached in order from left to right */
const int line_pins[8] ={A0, A1, A2, A3, A4, A5, A6, A7};

/* Initialization of objects for control the robot  */

/* Motors object*/
Motors robotMotors(DIR3, PWM3, DIR1, PWM1);

/* Buzzer object*/
Buzzer robotBuzzer(SPK);

/* LED object*/
Led robotLed(LED);

/* Button objects*/
PushButton button1(SW1, true, true);
PushButton button2(SW2, true, true);
PushButton button3(SW3, true, true);

/* Light Sensor objects*/
LineSensor robotLineSensor(line_pins);

/* Robot objects*/
lineFollowerRobot lineFollowerRobot(robotMotors,robotBuzzer,robotLed,button1,button2,button3,robotLineSensor);


void setup() {
  // put your setup code here, to run once:
  // Init Serial  -> for debugging
  Serial.begin(9600); 
  // Init Line Follower Robot
  lineFollowerRobot.init();

}

void loop() {
  
  /* Main control in robot robot.cpp and robot.h */
  lineFollowerRobot.robot_loop();
}



