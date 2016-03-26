#ifndef FIFO
#define FIFO
#define BufferSize 1000

#include "Arduino.h"

class Fifo
{
public:
  Fifo();
  byte take();
  bool add(byte value);
  bool available();
  void clear();
  bool almostFull();

private:
  byte buffArray[BufferSize];
  int posRead;
  int posWrite;
  int level;
};

#endif
