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
        buffer[0] = 0x1c;
        buffer[1] = 0x22;
        buffer[2] = 0x41;
        buffer[3] = 0x00;
        endPos = 3;
        break;
      case 41:  // )
        buffer[0] = 0x41;
        buffer[1] = 0x22;
        buffer[2] = 0x1c;
        buffer[3] = 0x00;
        endPos = 3;
        break;
      case 42:  // *
        buffer[0] = 0x08;
        buffer[1] = 0x2a;
        buffer[2] = 0x1c;
        buffer[3] = 0x2a;
        buffer[4] = 0x08;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 43:  // +
        buffer[0] = 0x08;
        buffer[1] = 0x08;
        buffer[2] = 0x3e;
        buffer[3] = 0x08;
        buffer[4] = 0x08;
        buffer[5] = 0x00;
        endPos = 5;
        break;
      case 44:  // ,
        buffer[0] = 0x05;
        buffer[1] = 0x06;
        buffer[2] = 0x00;
        endPos = 2;
       break;
      case 45:  // -
        buffer[0] = 0x08;
        buffer[1] = 0x08;
        buffer[2] = 0x08;
        buffer[3] = 0x08;
        buffer[4] = 0x00;
        endPos = 4;
      break;
      case 46:  // .
        buffer[0] = 0x03;
        buffer[1] = 0x03;
        buffer[2] = 0x00;
        endPos = 2;
      break;
      case 47:  // /
        buffer[0] = 0x03;
        buffer[1] = 0x04;
        buffer[2] = 0x18;
        buffer[3] = 0x60;
        buffer[4] = 0x00;
        endPos = 4;
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
        buffer[0] = 0x33;
        buffer[1] = 0x33;
        buffer[2] = 0x00;
        endPos = 2;
        break;
      case 59:  // ;
        buffer[0] = 0x35;
        buffer[1] = 0x36;
        buffer[2] = 0x00;
        endPos = 2;
        break;
      case 60:  // <
        buffer[0] = 0x08;
        buffer[1] = 0x14;
        buffer[2] = 0x22;
        buffer[3] = 0x41;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 61:  // =
        break;
      case 62:  // >
        buffer[0] = 0x41;
        buffer[1] = 0x22;
        buffer[2] = 0x14;
        buffer[3] = 0x08;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 63:  // ?
        buffer[0] = 0x20;
        buffer[1] = 0x40;
        buffer[2] = 0x45;
        buffer[3] = 0x48;
        buffer[4] = 0x30;
        buffer[5] = 0x00;
        endPos = 5;
        break;
      case 64:  // @
        break;
      case 65:  // A
        buffer[0] = 0x3f;
        buffer[1] = 0x44;
        buffer[2] = 0x44;
        buffer[3] = 0x3f;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 66:  // B
        buffer[0] = 0x7f;
        buffer[1] = 0x49;
        buffer[2] = 0x49;
        buffer[3] = 0x36;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 67:  // C
        buffer[0] = 0x3e;
        buffer[1] = 0x41;
        buffer[2] = 0x41;
        buffer[3] = 0x22;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 68:  // D
        buffer[0] = 0x7f;
        buffer[1] = 0x41;
        buffer[2] = 0x22;
        buffer[3] = 0x1c;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 69:  // E
        buffer[0] = 0x7f;
        buffer[1] = 0x49;
        buffer[2] = 0x49;
        buffer[3] = 0x41;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 70:  // F
        buffer[0] = 0x7f;
        buffer[1] = 0x48;
        buffer[2] = 0x48;
        buffer[3] = 0x40;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 71:  // G
        buffer[0] = 0x3e;
        buffer[1] = 0x41;
        buffer[2] = 0x45;
        buffer[3] = 0x26;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 72:  // H
        buffer[0] = 0x7f;
        buffer[1] = 0x08;
        buffer[2] = 0x08;
        buffer[3] = 0x7f;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 73:  // I
        buffer[0] = 0x41;
        buffer[1] = 0x7f;
        buffer[2] = 0x41;
        buffer[3] = 0x00;
        endPos = 3;
       break;
      case 74:  // J
        buffer[0] = 0x02;
        buffer[1] = 0x41;
        buffer[2] = 0x7e;
        buffer[3] = 0x40;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 75:  // K
        buffer[0] = 0x7f;
        buffer[1] = 0x08;
        buffer[2] = 0x14;
        buffer[3] = 0x22;
        buffer[4] = 0x41;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 76:  // L
        buffer[0] = 0x7f;
        buffer[1] = 0x01;
        buffer[2] = 0x01;
        buffer[3] = 0x01;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 77:  // M
        buffer[0] = 0x7f;
        buffer[1] = 0x20;
        buffer[2] = 0x10;
        buffer[3] = 0x20;
        buffer[4] = 0x7f;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 78:  // N
        buffer[0] = 0x7f;
        buffer[1] = 0x10;
        buffer[2] = 0x08;
        buffer[3] = 0x04;
        buffer[4] = 0x7f;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 79:  // O
        buffer[0] = 0x3e;
        buffer[1] = 0x41;
        buffer[2] = 0x41;
        buffer[3] = 0x3e;
        buffer[4] = 0x00;
        endPos = 4;
      break;
      case 80:  // P
        buffer[0] = 0x7f;
        buffer[1] = 0x48;
        buffer[2] = 0x48;
        buffer[3] = 0x30;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 81:  // Q
        buffer[0] = 0x3e;
        buffer[1] = 0x41;
        buffer[2] = 0x45;
        buffer[3] = 0x42;
        buffer[4] = 0x3d;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 82:  // R
        buffer[0] = 0x7f;
        buffer[1] = 0x4c;
        buffer[2] = 0x4a;
        buffer[3] = 0x31;
        buffer[4] = 0x00;
        endPos = 4;
       break;
      case 83:  // S
        buffer[0] = 0x32;
        buffer[1] = 0x49;
        buffer[2] = 0x49;
        buffer[3] = 0x26;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 84:  // T
        buffer[0] = 0x40;
        buffer[1] = 0x40;
        buffer[2] = 0x7f;
        buffer[3] = 0x40;
        buffer[4] = 0x40;
        buffer[5] = 0x00;
        endPos = 5;
        break;
      case 85:  // U
        buffer[0] = 0x7e;
        buffer[1] = 0x01;
        buffer[2] = 0x01;
        buffer[3] = 0x7e;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 86:  // V
        buffer[0] = 0x7c;
        buffer[1] = 0x02;
        buffer[2] = 0x01;
        buffer[3] = 0x02;
        buffer[4] = 0x7c;
        buffer[5] = 0x00;
        endPos = 5;
        break;
      case 87:  // W
        buffer[0] = 0x7f;
        buffer[1] = 0x02;
        buffer[2] = 0x0c;
        buffer[3] = 0x02;
        buffer[4] = 0x7f;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 88:  // X
        buffer[0] = 0x63;
        buffer[1] = 0x14;
        buffer[2] = 0x08;
        buffer[3] = 0x14;
        buffer[4] = 0x63;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 89:  // Y
        buffer[0] = 0x60;
        buffer[1] = 0x10;
        buffer[2] = 0x0f;
        buffer[3] = 0x10;
        buffer[4] = 0x60;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 90:  // Z
        buffer[0] = 0x43;
        buffer[1] = 0x45;
        buffer[2] = 0x49;
        buffer[3] = 0x51;
        buffer[4] = 0x61;
        buffer[5] = 0x00;
        endPos = 5;
       break;
      case 91:  // [
        buffer[0] = 0x7f;
        buffer[1] = 0x41;
        buffer[2] = 0x41;
        buffer[3] = 0x00;
        endPos = 3;
        break;
      case 92:  // \
        buffer[0] = 0x60;
        buffer[1] = 0x18;
        buffer[2] = 0x04;
        buffer[3] = 0x03;
        buffer[4] = 0x00;
        endPos = 4;
        break;
      case 93:  // ]
        buffer[0] = 0x41;
        buffer[1] = 0x41;
        buffer[2] = 0x7f;
        buffer[3] = 0x00;
        endPos = 3;
       break;
      case 94:  // ^
        break;
      case 95:  // _
        buffer[0] = 0x01;
        buffer[1] = 0x01;
        buffer[2] = 0x01;
        buffer[3] = 0x01;
        buffer[4] = 0x00;
        endPos = 4;
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
