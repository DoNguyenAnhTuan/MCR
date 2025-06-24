#ifndef LED_H 
#define LED_H 
#include <Arduino.h>

class Led
{
  private:
    byte led_pin;
    byte state;
    unsigned long lastTimeBlinked;

	public:
    Led() {}

		Led(byte led_pin);
    void init(byte defaultState);

		void On();
    void Off();
    void Toggle();
    void setLong(unsigned int _timer);
    void blinkingLed(unsigned int _timer);
    bool isPoweredOn();
};

#endif
