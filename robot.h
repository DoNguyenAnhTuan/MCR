#ifndef ROBOT_H 
#define ROBOT_H 
#include <Arduino.h>
#include <Wire.h>
// #include <avr/interrupt.h>

#include <Servo.h>
#include "motors.h"
#include "buzzer.h"
#include "led.h"
#include "pushButton.h"
#include "lineSensor.h"

#define ROBOT_SPEED 25

class lineFollowerRobot
{
  private: 
    Motors robotMotors;
    Buzzer robotBuzzer;
    Led robotLed;
    PushButton button1;
    PushButton button2;
    PushButton button3;
    LineSensor robotLineSensor;

    // Servo center = 90 
    // 65 < Servo < 90 => Turn RIGHT (25 degree) 
    // 90 < Servo < 110 => Turn LEFT (25 degree)
    // - => Turn Right
    // + => Turn Left

    int servo_center = 90; // Change this number based on your robot
    Servo myservo;

 
    enum RobotMode{
      INTRODUCTION_STATE,
      MAIN_MENU,
      SENSOR_CALIB,
      SHOW_MASK_VALUE,
      SERVO_CALIB,
      MOTOR_CHECK,
      RACING,
    };

    enum RunCase{
      STOP =0 ,

      NORMAL_TRACE = 11,               //11
      LARGE_LEFT_TURN = 12,            //12
      LARGE_RIGHT_TURN =13,            //13

      CROSS_LINE_ONE =21,              //21
      CROSS_LINE_TWO =22,              //22
      TRACE_AFTER_CROSS_LINE =23,      //23

      TURN_LEFT_90=31,                 //31
      END_TURN_LEFT_90=32,             //32

      TURN_RIGHT_90=41,                //41
      END_TURN_RIGHT_90=42,            //42

      RIGHT_HALF_LANE_ONE=51,          //51
      RIGHT_HALF_LANE_TWO=52,          //52
      CHANGE_RIGHT_LANE=53,            //53
      END_CHANGE_RIGHT_LANE=54,        //54

      LEFT_HALF_LANE_ONE=61,           //61
      LEFT_HALF_LANE_TWO=62,           //62
      CHANGE_LEFT_LANE=63,             //63
      END_CHANGE_LEFT_LANE=64,         //64
    };

    int state;
    int robot_runcase;
    int MenuCount;
    bool drawMenu ;
    byte sensor;


    int speed_run = ROBOT_SPEED; // percentage 30%

    int cnt1;
    unsigned long new_time;
  public:
    lineFollowerRobot() {} //do not use
    lineFollowerRobot(Motors &robotMotors,
                      Buzzer &robotBuzzer,
                      Led &robotLed,
                      PushButton &button1,
                      PushButton &button2,
                      PushButton &button3,
                      LineSensor &robotLineSensor);  /// Room for include pid controller
    
    void init();
    void sensor_calibration();
    void handle_calibration();
    void motor_check();
    void show_position();
    void menu_control();
    void run(); /// Function to handle the race
    void robot_loop();// function to control the rsobot by usings the button

    
    // Maksing method 
    byte sensorMask (byte sensor,  byte MASK);

    // Handle speed control
    void handle_and_speed(int angle, int speed);

    // Check current state on the road
    int check_crossline(byte sensor);
    int check_rightline(byte sensor);
    int check_leftline(byte sensor);

};

#endif
