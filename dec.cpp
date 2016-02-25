#include "dec.h"
#include "Arduino.h"

Dec::Dec()
{
  reset();
}

bool Dec::charReady()
{
  if(digit)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool Dec::add(byte part)
{
  if(part >= 48 && part <= 57)          //numbers
  {
    value = part - 48;
  }
  else                                  //not a valid character
  {
    return false;
  }

  if(digit == 0)
  {
    digit = 1;
    buffer = value * 100;
    Serial.print(char(part));
  }
  else if(digit == 1)
  {
    digit = 2;
    buffer += value * 10;
    Serial.print(char(part));
  }
  else
  {
    digit = 0;
    buffer += value;
    Serial.print(char(part));
    Serial.print("\t");
  }
  
  if(buffer > 255)
  {
    return false;
  }
  else
  {
    return true;
  }
}

byte Dec::character()
{
  digit = 0;
  return buffer;
}

void Dec::reset()
{
  digit = 0;
  buffer = 0;
}

