#include "baudot.h"
#include "Arduino.h"

Baudot::Baudot()
{
  reset();
}

void Baudot::reset()
{
  bMode = switchToLetters;
  buffer = 0;
}

bool Baudot::charReady()
{
  switch(bMode)
  {
    case switchToLetters:
    case switchToFigures:
      return true;
      break;
    default:
      if(buffer > 0)
      {
        return true;
      }
      else
      {
        return false;
      }
  }
  
  // execution should never reach this point!
  return false; 
}

byte Baudot::character()
{
  byte tmp = 0;
  if(bMode == switchToLetters)
  {
    bMode = letters;
    tmp = 31;
  }
  else if(bMode == switchToFigures)
  {
    bMode = figures;
    tmp = 27;
  }
  else
  {
    tmp = buffer;
    buffer = 0;
  }
  // for compatibility with 8-Bit paper tape and reader allways punch the high 3 holes
  //tmp += 224;
  return tmp;
}

bool Baudot::set(byte input)
{
  // lower uppercase characters
  if(input >= 65 && input <= 90)
  {
    input += 32;
  }

  baudotMode nextChar = bMode;
  
  switch(input)
  {
    case 'a':
      buffer = 24;
      nextChar = letters;
      break;
    case 'b':
      buffer = 19;
      nextChar = letters;
      break;
    case 'c':
      buffer = 14;
      nextChar = letters;
      break;
    case 'd':
      buffer = 18;
      nextChar = letters;
      break;
    case 'e':
      buffer = 16;
      nextChar = letters;
      break;
    case 'f':
      buffer = 22;
      nextChar = letters;
      break;
    case 'g':
      buffer = 11;
      nextChar = letters;
      break;
    case 'h':
      buffer = 5;
      nextChar = letters;
      break;
    case 'i':
      buffer = 12;
      nextChar = letters;
      break;
    case 'j':
      buffer = 26;
      nextChar = letters;
      break;
    case 'k':
      buffer = 30;
      nextChar = letters;
      break;
    case 'l':
      buffer = 9;
      nextChar = letters;
      break;
    case 'm':
      buffer = 7;
      nextChar = letters;
      break;
    case 'n':
      buffer = 6;
      nextChar = letters;
      break;
    case 'o':
      buffer = 3;
      nextChar = letters;
      break;
    case 'p':
      buffer = 13;
      nextChar = letters;
      break;
    case 'q':
      buffer = 29;
      nextChar = letters;
      break;
    case 'r':
      buffer = 10;
      nextChar = letters;
      break;
    case 's':
      buffer = 20;
      nextChar = letters;
      break;
    case 't':
      buffer = 1;
      nextChar = letters;
      break;
    case 'u':
      buffer = 28;
      nextChar = letters;
      break;
    case 'v':
      buffer = 15;
      nextChar = letters;
      break;
    case 'w':
      buffer = 25;
      nextChar = letters;
      break;
    case 'x':
      buffer = 23;
      nextChar = letters;
      break;
    case 'y':
      buffer = 21;
      nextChar = letters;
      break;
    case 'z':
      buffer = 17;
      nextChar = letters;
      break;
    case 13:                      // TODO: check if CR and LF allways are together
      buffer = 2;
      break;
    case ' ':
      buffer = 4;
      break;
    case 10:                      // TODO: check if CR and LF allways are together
      buffer = 8;
      break;
    case '0':
      buffer = 13;
      nextChar = figures;
      break;
    case '1':
      buffer = 29;
      nextChar = figures;
      break;
    case '2':
      buffer = 25;
      nextChar = figures;
      break;
    case '3':
      buffer = 16;
      nextChar = figures;
      break;
    case '4':
      buffer = 10;
      nextChar = figures;
      break;
    case '5':
      buffer = 1;
      nextChar = figures;
      break;
    case '6':
      buffer = 21;
      nextChar = figures;
      break;
    case '7':
      buffer = 28;
      nextChar = figures;
      break;
    case '8':
      buffer = 12;
      nextChar = figures;
      break;
    case '9':
      buffer = 3;
      nextChar = figures;
      break;
    case ',':
      buffer = 6;
      nextChar = figures;
      break;
    case '.':
      buffer = 7;
      nextChar = figures;
      break;
    case '-':
      buffer = 24;
      nextChar = figures;
      break;      
    case '+':
      buffer = 17;
      nextChar = figures;
      break;
    case '?':
      buffer = 19;
      nextChar = figures;
      break;
    case ':':
      buffer = 14;
      nextChar = figures;
      break;
    case '=':
      buffer = 15;
      nextChar = figures;
      break;
    case '(':
    case '[':
    case '{':
    case '<':
      buffer = 30;
      nextChar = figures;
      break;
    case ')':
    case ']':
    case '}':
    case '>':
      buffer = 9;
      nextChar = figures;
      break;
    case '/':
      buffer = 23;
      nextChar = figures;
      break;
    case '\'':
      buffer = 20;
      nextChar = figures;
      break;
    case '\a':  // bell
      buffer = 26;
      nextChar = figures;
      break;
    case 5:     // ENQ resp. "who are you?"
      buffer = 18;
      nextChar = figures;
      break;
    default:
      buffer = 0;
      break;
  }

  if(bMode != nextChar)
  {
    if(nextChar == figures)
    {
      bMode = switchToFigures;
    }
    else
    {
      bMode = switchToLetters;
    }
  }

  if(buffer == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

