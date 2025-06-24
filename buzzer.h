#ifndef BUZZER_H 
#define BUZZER_H 
#include <Arduino.h>

class Buzzer
{
  private:
    byte buzzer_pin;
    byte state;
    unsigned long lastTimeBeeped;
    // unsigned long beepDelay;

	public:
    Buzzer() {}
    
		Buzzer(byte buzzer_pin);
    void init();
    void init(byte defaultState);
		void setBeep(unsigned int _timer);
    void beepLong(unsigned int _timer);

    void Toggle();
    bool isPowerOn();
    void On();
    void Off();
};

#endif