#ifndef HUMAN_H
#define HUMAN_H

#include "Arduino.h"

#define maxSize 6

class Human
{
public:
  Human();
  bool charReady();
  byte character();
  bool add(byte input);
  void reset();
  
private:
  byte buffer[maxSize];
  int endPos;
  int curPos;
};

#endif
