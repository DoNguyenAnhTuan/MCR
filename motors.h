#ifndef MOTORS_H 
#define MOTORS_H 
#include <Arduino.h>

class Motors
{
  private:
    byte left_dir;
    byte right_dir;
    byte left_pwm;
    byte right_pwm;
    byte state;
	public:
    Motors() {}

		Motors(byte left_dir, byte left_pwm, byte right_dir, byte right_pwm);
    void init();
		void setSpeed(int left_speed, int right_speed);
};

#endif
