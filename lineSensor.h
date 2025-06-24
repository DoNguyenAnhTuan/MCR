#ifndef LINE_SENSOR_H 
#define LINE_SENSOR_H 
#include <avdweb_AnalogReadFast.h>


// This library is used for increasing the reading speed of the pin
class LineSensor
{
  private:
    int pin[8]; //= {A0, A1, A2, A3, A4, A5, A6, A7};
    unsigned int sensor_value[8];
    unsigned int v_compare[8] = {900,900,900,900,900,900,900,900};
    byte sensor; // 8 bit value of line sensor -> Showing the current position of the line.

    unsigned int minOfMaxSensorValue[8]= {500,500,500,500,500,500,500,500};
    unsigned int maxOfMinSensorValue[8] = {50,50,50,50,50,50,50,50};

  public:
    LineSensor() {}

    LineSensor(int pin[8]); 

    void init();
    void readADC();
    byte readSensor();

    void update_white();
    void update_black();
    void calibration();

    void debug();
    
};



#endif