#include "led.h"

Led::Led(byte led_pin)
{
  this -> led_pin = led_pin;
  lastTimeBlinked = millis();
}

void Led::init(byte defaultState)
{
  pinMode(led_pin, OUTPUT);
  if (defaultState == HIGH)
  {
    On();
  }
  else{
    Off();
  }
}

void Led::On()
{
  state = HIGH;
  digitalWrite(led_pin, HIGH);
}

void Led::Off()
{
  state = LOW;
  digitalWrite(led_pin, LOW);
}

bool Led::isPoweredOn()
{
  return (state == HIGH);
}

void Led::Toggle()
{
  if(isPoweredOn())
  {
    Off();
  }
  else {
    On();
  }
}

void Led::setLong(unsigned int _timer)
{
  while(_timer > 0){
  unsigned long timeNow = millis();
  On();
  if (timeNow - lastTimeBlinked >= 1)
    {
      lastTimeBlinked = timeNow;
      _timer--;
    }
  }
   Off();
}

void Led::blinkingLed(unsigned int _timer)
{
   unsigned long timeNow = millis();
  if (timeNow - lastTimeBlinked > _timer)
    {
      lastTimeBlinked = timeNow;
      Toggle();
    }
}

/////
