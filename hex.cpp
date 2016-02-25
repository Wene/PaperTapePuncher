#include "hex.h"
#include "Arduino.h"

Hex::Hex()
{
  reset();
}

bool Hex::charReady()
{
  return first;
}

bool Hex::add(byte part)
{
  if(part >= 48 && part <= 57)          //numbers
  {
    value = part - 48;
  }
  else if(part >=65 && part <= 70)      //upper case letters
  {
    value = part - 65 + 10;
  }
  else if(part >= 97 && part <= 102)    //lower case letters
  {
    value = part - 97 + 10;
  }
  else                                  //not a valid character
  {
    return false;
  }

  if(first)
  {
    first = false;
    buffer = value << 4;
    Serial.print(char(part));
  }
  else
  {
    first = true;
    buffer |= value;
    Serial.print(char(part));
    Serial.print("\t");
  }
  return true;
}

byte Hex::character()
{
  first = true;
  return buffer;
}

void Hex::reset()
{
  first = true;
  buffer = 0;
}

