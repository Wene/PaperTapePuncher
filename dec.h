#ifndef DEC_H
#define DEC_H

#include "Arduino.h"

class Dec {
public:
  Dec();
  bool charReady();
  byte character();
  bool add(byte part);
  void reset();
  
private:
  unsigned int buffer;
  byte digit;
  unsigned int value;
};

#endif
