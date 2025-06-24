#include "Arduino.h"
#include "motors.h"

#define MAX_SPEED 100
#define MIN_SPEED 0


Motors::Motors(byte left_dir, byte left_pwm, byte right_dir, byte right_pwm)
{
  this -> left_dir = left_dir;
  this -> left_pwm = left_pwm;
  this -> right_dir = right_dir;
  this -> right_pwm = right_pwm;
}

void Motors::init()
{
  // Configure motor control pins to output mode
  pinMode(left_dir, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(right_dir, OUTPUT);
  pinMode(right_pwm, OUTPUT);
}

void Motors::setSpeed(int left_speed, int right_speed)
{
  if(left_speed >= 0)
  {
    // run forward 
    digitalWrite(left_dir, HIGH);
  }
  else{
    left_speed = -left_speed;
    digitalWrite(left_dir, LOW);
  } 

  if(right_speed >= 0)
  {
    // run forward 
    digitalWrite(right_dir, HIGH);
  }
  else{
    right_speed = -right_speed;
    digitalWrite(right_dir, LOW);
  } 

  if (left_speed > MAX_SPEED) left_speed = MAX_SPEED;
  if (left_speed < MIN_SPEED ) left_speed = MIN_SPEED;

  if (right_speed > MAX_SPEED) right_speed = MAX_SPEED;
  if (right_speed < MIN_SPEED ) right_speed = MIN_SPEED;


  left_speed  = left_speed * 255/100;
  right_speed  = right_speed * 255/100;
  
  analogWrite(left_pwm, left_speed);
  analogWrite(right_pwm, right_speed);

  
}

