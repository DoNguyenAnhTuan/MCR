#include "Arduino.h"
#include "lineSensor.h"

LineSensor::LineSensor(int pin[8])
{
  // pin = new int[8];
  for (int i = 0; i < 8; i++)
  {
    this -> pin[i] = pin[i];
  }
}

void LineSensor::init()
{
  for (int i =0; i < 8; i++)
  {
    pinMode(pin[i], INPUT);
  }
}

void LineSensor::readADC()
{
  for(int i = 0; i < 8 ; i++)
  {
    sensor_value[i] = analogReadFast(pin[i]);
  }
}

byte LineSensor::readSensor()
{
  byte temp = 0; //0b00000000
  readADC();
  for ( int i = 0; i < 8; i++)
  {
    temp = temp << 1;
    if (sensor_value[i] > v_compare[i]) 
    {
      temp |= 0x01;//0b00000001 
    }
    else
    {
      temp &= 0xfe;//0b11111110
    }

  }
  return (temp); // return value of line sensor (in decimal type, but this can be processed as the binary and heximal too.)
}


void LineSensor::update_white()
{
  // int i =0;
  readADC();
	for (int i=0; i<8; i++)
	{
		minOfMaxSensorValue[i] = sensor_value[i];
	}
	for (int i=0; i<8; i++)
	{
		v_compare[i] = (maxOfMinSensorValue[i] + minOfMaxSensorValue[i])/2;
	}
}

void LineSensor::update_black()
{
  // int i =0;
  readADC();
  for (int i=0; i<8; i++)
	{
		maxOfMinSensorValue[i] = sensor_value[i];
	}
	for (int i=0; i<8; i++)
	{
		v_compare[i] = (maxOfMinSensorValue[i] + minOfMaxSensorValue[i])/2;
	}
}

void LineSensor::debug()
{
  // int i =0;
  byte mask =0;
  readADC();

  Serial.print("Sensor Value: ");
  for (int i = 0; i < 8; i++) {
  Serial.print(sensor_value[i]);
  Serial.print(" ");
  }

  Serial.println();
  Serial.print("On Black: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(maxOfMinSensorValue[i]);
    Serial.print(" ");
  }


  Serial.println();
  Serial.print("On White: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(minOfMaxSensorValue[i]);
    Serial.print(" ");
  }

  Serial.println();
  Serial.print("V Compare: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(v_compare[i]);
    Serial.print(" ");
  }

  Serial.println();
  mask = readSensor();
  Serial.print("MASK: ");
  Serial.print(mask, BIN);
  Serial.println();
  Serial.println("---------------------------");
  

}



