#include "human.h"
#include "Arduino.h"


Human::Human()
{
  reset();
}

bool Human::charReady()
{
  if(curPos > endPos)
  {
    return false;
  }
  else
  {
    return true;
  }
}

byte Human::character()
{
  if(charReady())
  {
    curPos++;
    return buffer[curPos - 1];
  }
  else
  {
    return 0;
  }
}

void Human::reset()
{
  for(int i = 0; i < maxSize; i++)
  {
    buffer[i] = 0;
  }
  endPos = 0;
  curPos = 0;
}

bool Human::add(byte input)
{
  if(input >= 32 && input <= 126)
  {
    reset();
    switch(input)
    {
      case 32:  // space
        buffer[0] = 0x00;
        buffer[1] = 0x00;
        buffer[2] = 0x00;
        endPos = 2;
        break;
      case 33:  // !
        buffer[0] = 0x7b;
        buffer[1] = 0x7b;
        buffer[2] = 0x00;
        endPos = 2;
        break; 
      case 34:  // "
        buffer[0] = 0x70;
        buffer[1] = 0x00;
        buffer[2] = 0x70;
        buffer[3] = 0x00;
        endPos = 3;
       break;
      case 35:  // #
        break;
      case 36:  // $
        break;
      case 37:  // %
        break;
      case 38:  // &
        break;
      case 39:  // '
        break;
      case 40:  // (
        break;
      case 41:  // )
        break;
      case 42:  // *
        break;
      case 43:  // +
        break;
      case 44:  // ,
        buffer[0] = 0x05;
        buffer[1] = 0x06;
        buffer[2] = 0x00;
        endPos = 2;
       break;
      case 45:  // -
        break;
      case 46:  // .
        buffer[0] = 0x03;
        buffer[1] = 0x03;
        buffer[2] = 0x00;
        endPos = 2;
      break;
      case 47:  // /
        break;
      case 48:  // 0
        buffer[0] = 0x3e;
        buffer[1] = 0x45;
        buffer[2] = 0x49;
        buffer[3] = 0x51;
        buffer[4] = 0x3e;
        buffer[5] = 0x00;
        endPos = 5;
        break;
      case 49:  // 1
        buffer[0] = 0x21;
        buffer[1] = 0x7f;
        buffer[2] = 0x01;
        buffer[3] = 0x00;
        endPos = 3;
        break;
      case 50:  // 2
        buffer[0] = 0x23;
        buffer[1] = 0x45;
        buffer[2] = 0x49;
        buffer[3] = 0x31;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 51:  // 3
        buffer[0] = 0x42;
        buffer[1] = 0x51;
        buffer[2] = 0x69;
        buffer[3] = 0x46;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 52:  // 4
        buffer[0] = 0x0c;
        buffer[1] = 0x14;
        buffer[2] = 0x24;
        buffer[3] = 0x7f;
        buffer[4] = 0x04;
        buffer[5] = 0x00;
        endPos = 5;
        break;
      case 53:  // 5
        buffer[0] = 0x72;
        buffer[1] = 0x51;
        buffer[2] = 0x51;
        buffer[3] = 0x4e;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 54:  // 6
        buffer[0] = 0x1e;
        buffer[1] = 0x29;
        buffer[2] = 0x49;
        buffer[3] = 0x46;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 55:  // 7
        buffer[0] = 0x40;
        buffer[1] = 0x4f;
        buffer[2] = 0x50;
        buffer[3] = 0x60;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 56:  // 8
        buffer[0] = 0x36;
        buffer[1] = 0x49;
        buffer[2] = 0x49;
        buffer[3] = 0x36;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 57:  // 9
        buffer[0] = 0x31;
        buffer[1] = 0x49;
        buffer[2] = 0x4a;
        buffer[3] = 0x3c;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 58:  // :
        break;
      case 59:  // ;
        break;
      case 60:  // <
        break;
      case 61:  // =
        break;
      case 62:  // >
        break;
      case 63:  // ?
        break;
      case 64:  // @
        break;
      case 65:  // A
        break;
      case 66:  // B
        break;
      case 67:  // C
        break;
      case 68:  // D
        break;
      case 69:  // E
        break;
      case 70:  // F
        break;
      case 71:  // G
        break;
      case 72:  // H
        break;
      case 73:  // I
        break;
      case 74:  // J
        break;
      case 75:  // K
        break;
      case 76:  // L
        break;
      case 77:  // M
        break;
      case 78:  // N
        break;
      case 79:  // O
        break;
      case 80:  // P
        break;
      case 81:  // Q
        break;
      case 82:  // R
        break;
      case 83:  // S
        break;
      case 84:  // T
        break;
      case 85:  // U
        break;
      case 86:  // V
        break;
      case 87:  // W
        break;
      case 88:  // X
        break;
      case 89:  // Y
        break;
      case 90:  // Z
        break;
      case 91:  // [
        break;
      case 92:  // \
        break;
      case 93:  // ]
        break;
      case 94:  // ^
        break;
      case 95:  // _
        break;
      case 96:  // `
        break;
      case 97:  // a
        break;
      case 98:  // b
        break;
      case 99:  // c
        break;
      case 100:  // d
        break;
      case 101:  // e
        break;
      case 102:  // f
        break;
      case 103:  // g
        break;
      case 104:  // h
        break;
      case 105:  // i
        break;
      case 106:  // j
        break;
      case 107:  // k
        break;
      case 108:  // l
        break;
      case 109:  // m
        break;
      case 110:  // n
        break;
      case 111:  // o
        break;
      case 112:  // p
        break;
      case 113:  // q
        break;
      case 114:  // r
        break;
      case 115:  // s
        break;
      case 116:  // t
        break;
      case 117:  // u
        break;
      case 118:  // v
        break;
      case 119:  // w
        break;
      case 120:  // x
        break;
      case 121:  // y
        break;
      case 122:  // z
        break;
      case 123:  // {
        break;
      case 124:  // |
        break;
      case 125:  // }
        break;
      case 126:  // ~
        break;
      default:
        return false;
        break;
    }
    return true;
  }
  else
  {
    return false;
  }
}
