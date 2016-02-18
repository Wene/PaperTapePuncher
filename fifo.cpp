#include "fifo.h"
#include "Arduino.h"

Fifo::Fifo()
{
  for(int i = 0; i < BufferSize; i++)
  {
    buffArray[i] = 0;
  }
  posWrite = 0;
  posRead = 0;
  level = 0;
}

byte Fifo::take(bool &ok)
{
  if(level)
  {
    level--;
    byte value = buffArray[posRead];
    posRead++;
    if(posRead >= BufferSize)
    {
      posRead = 0;
    }
    ok = true;
    return value;
  }
  else
  {
    ok = false;
    return 0;
  }
}

bool Fifo::add(byte value)
{
  buffArray[posWrite] = value;
  posWrite++;
  level++;
  if(posWrite >= BufferSize)
  {
    posWrite = 0;
  }
  if(level > BufferSize)
  {
    level = 0;
    posRead = posWrite;
    return false;
  }
  else
  {
    return true;
  }
}

