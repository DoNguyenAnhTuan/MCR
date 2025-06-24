#ifndef PUSHBUTTON_H 
#define PUSHBUTTON_H 
#include <Arduino.h>


class PushButton
{
  private:
    byte pin;
    byte state;
    bool isPullup;
    bool internalPullUpActivated;

    unsigned long lastTimeStateChanged;
    unsigned long debounceDelay;

    byte readState();

  public:
    PushButton() {}
    PushButton(byte pin, bool isPullup, bool internalPullUpActivated); 


    void init();
    bool isPressed();

};



#endif