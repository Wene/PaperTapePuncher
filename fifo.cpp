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

byte Fifo::take()
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
    return value;
  }
  else
  {
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
    clear();
    return false;
  }
  else
  {
    return true;
  }
}

bool Fifo::available()
{
  if(level)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Fifo::clear()
{
  posRead = posWrite;
  level = 0;
}

bool Fifo::almostFull()
{
  if(level > BufferSize / 3)
  {
    return true;
  }
  else
  {
    return false;
  }
}

