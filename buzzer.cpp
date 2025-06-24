#include "buzzer.h"

Buzzer::Buzzer(byte buzzer_pin)
{
  this -> buzzer_pin = buzzer_pin;
  lastTimeBeeped = millis();
}

void Buzzer::init()
{
  pinMode(buzzer_pin, OUTPUT);
}

void Buzzer::init(byte defaultState)
{
  init();
  if (defaultState == HIGH)
  {
    On();
  }
  else
  {
    Off();
  }
}

void Buzzer::On()
{
  state = HIGH;
  digitalWrite(buzzer_pin, HIGH);
}

void Buzzer::Off()
{
  state = LOW;
  digitalWrite(buzzer_pin, LOW);
}

bool Buzzer::isPowerOn()
{
  return (state == HIGH);
}

void  Buzzer::Toggle()
{
  if(isPowerOn())
  {
    Off();
  }
  else {
    On();
  }
}


void Buzzer::setBeep(unsigned int _timer)
{
  while(_timer > 0){
  unsigned long timeNow = millis();
  On();
  if (timeNow - lastTimeBeeped >= 1)
    {
      lastTimeBeeped = timeNow;
      _timer--;
    }
  }
   Off();
}

void Buzzer::beepLong(unsigned int _timer)
{
   unsigned long timeNow = millis();
  if (timeNow - lastTimeBeeped > _timer)
  {
    lastTimeBeeped = timeNow;
    Toggle();
  }
}

// Last line of program
