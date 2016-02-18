#ifndef FIFO
#define FIFO
#define BufferSize 1000

#include "Arduino.h"


class Fifo
{
public:
  Fifo();
  byte take(bool &ok);
  bool add(byte value);

private:
  byte buffArray[BufferSize];
  int posRead;
  int posWrite;
  int level;
};


#endif
