#ifndef HEX_H
#define HEX_H

#include "Arduino.h"

class Hex
{
public:
  Hex();
  bool charReady();
  byte character();
  bool add(byte part);
  void reset();
  
private:  
  byte buffer;
  bool first;
  byte value;
};

#endif
