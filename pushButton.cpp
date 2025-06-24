#include "Arduino.h"
#include "pushButton.h"


PushButton::PushButton(byte pin, bool isPullup, bool internalPullUpActivated)
{
  this -> pin = pin;
  this -> isPullup = isPullup;
  this -> internalPullUpActivated = internalPullUpActivated;


  // this attributes are not similar to the parameters of the function -> do not need "this"
  lastTimeStateChanged = millis();
  debounceDelay = 15;
}

void PushButton::init()
{

  if (isPullup && internalPullUpActivated)
  {
    pinMode(pin, INPUT_PULLUP);
  }
  else
  {
    pinMode(pin, INPUT);
  }
  // state = digitalRead(pin);
}

byte PushButton::readState()
{
  unsigned long timeNow = millis();
  if (timeNow - lastTimeStateChanged > debounceDelay){
    byte newState = digitalRead(pin);
    if (newState != state){
      state = newState;
      lastTimeStateChanged = timeNow;
    }
  }
  return state;
}

bool PushButton::isPressed()
{
 return readState();
}



