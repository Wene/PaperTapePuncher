#ifndef BAUDOT_H
#define BAUDOT_H

#include "Arduino.h"

class Baudot
{
public:
  Baudot();
  bool charReady();
  byte character();
  bool set(byte input);
  void reset();
  
private:
  enum baudotMode {letters, figures, switchToLetters, switchToFigures};
  baudotMode bMode;
  byte buffer;
};


#endif
