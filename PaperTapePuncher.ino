/* This software is written for Arduino boards and turn it into a
   Control unit replacement for FACIT Paper tape puncher. */

#include "fifo.h"
#include "hex.h"
#include "dec.h"
#include "human.h"
#include "baudot.h"

#define PinBit0 10
#define PinBit1 2
#define PinBit2 3
#define PinBit3 4
#define PinBit4 5
#define PinBit5 6
#define PinBit6 7
#define PinBit7 8
#define PinTransportHole 9
#define PinTransportMotor 11
#define PinStepSensor 12

#define highTime 2
#define lowTime 18
#define waitTime 5000

#define XON 17
#define XOFF 19

int pins[] = {PinBit0, PinBit1, PinBit2, PinBit3, PinBit4, PinBit5, PinBit6, PinBit7};

enum writeMode {error, ascii, binary, hex, dec, baudot, human};
bool simulationMode = true;
enum baudotMode {letters, figures};
writeMode mode = error;

Fifo writeBuffer;
Hex hexBuffer;
Dec decBuffer;
Human humanBuffer;
Baudot baudotBuffer;

unsigned long lastTime = 0;
unsigned long now = 0;
bool isHigh = false;
int value = 0;
byte character = 0;
bool good = true;

bool xonSendt = true;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  // initialize the input pins
  pinMode(PinBit0, OUTPUT); // bit 0
  pinMode(PinBit1, OUTPUT); // bit 1
  pinMode(PinBit2, OUTPUT); // bit 2
  pinMode(PinBit3, OUTPUT); // bit 3
  pinMode(PinBit4, OUTPUT); // bit 4
  pinMode(PinBit5, OUTPUT); // bit 5
  pinMode(PinBit6, OUTPUT); // bit 6
  pinMode(PinBit7, OUTPUT); // bit 7 or parity
  pinMode(PinTransportHole, OUTPUT);   // transport hole
  pinMode(PinTransportMotor, OUTPUT);  // Motor step
  pinMode(PinStepSensor, INPUT);       // Sensor for steps from manual operation
}

void loop() {

  //clear input buffer
  while(Serial.available())
  {
    Serial.read();
  }

  //print prompt
  Serial.println();
  Serial.println("Select mode: (H)uman readable, (A)SCII, (B)inary, HE(X), (D)ecimal, (5)-Bit Baudot");
  Serial.print("Toggle (S)imulation mode: currently ");
  if(simulationMode)
  {
    Serial.println("on");
  }
  else
  {
    Serial.println("off");
  }
  while(!Serial.available())
  {
    delay(10);
  }
  value = Serial.read();
  character = value;
  Serial.println();
  switch(character)
  {
    case 'h':
    case 'H':
      mode = human;
      Serial.println("Human readable mode - only ASCII allowed. Enter a char over 127 to exit.");
      break;
    case 'x':
    case 'X':
      mode = hex;
      Serial.println("HEX mode - Enter non HEX character to exit");
      break;
    case 'd':
    case 'D':
      mode = dec;
      Serial.println("Decimal mode: Enter 3-digit numbers. Invalid input to exit");
      break;
    case 'b':
    case 'B':    
      mode = binary;
      Serial.print("Binary mode - Wait for timeout to exit.");
      lastTime = millis();
      break;
    case 'a':
    case 'A':
      mode = ascii;
      Serial.println("ASCII mode - Enter a char over 127 to exit.");
      break;
    case '5':
      mode = baudot;
      Serial.println("5-Bit Baudot mode - Press escape to exit.");
      break;
    case 's':
    case 'S':
      simulationMode = !simulationMode;
      break;
    default:
      mode = error;
      Serial.println("Error - could not interpret your selection. Try again.");
      break;
  }
  Serial.println();   

  //punch in selected mode
  while(isHigh || mode != error)
  {
    while(Serial.available())
    {
      good = true;
      value = Serial.read();
      if(value >= 0 && value < 256)
      {
        switch(mode)
        {
          case error:
            break;
          case hex:
            if(hexBuffer.add(value))
            {
              if(hexBuffer.charReady())
              {
                good = writeBuffer.add(hexBuffer.character());
              }
            }
            else
            {
              mode = error;
              hexBuffer.reset();
              Serial.println();
              Serial.println("Input error - abort");
              Serial.println();
            }
            break;
          case human:
            if(humanBuffer.add(value))
            {
              while(humanBuffer.charReady() && good)
              {
                good = writeBuffer.add(humanBuffer.character());
              }
            }
            else
            {
              mode = error;
              humanBuffer.reset();
              Serial.println();
              Serial.println("Input error - abort");
              Serial.println(); 
            }
            break;
          case dec:
            if(decBuffer.add(value))
            {
              if(decBuffer.charReady())
              {
                good = writeBuffer.add(decBuffer.character());
              }
            }
            else
            {
              mode = error;
              decBuffer.reset();
              Serial.println();
              Serial.println("Input error - abort");
              Serial.println();
            }
            break;
          case ascii:
            if(value <= 127)
            {
              int count = 0;
              for(int i = 0; i < 7; i++)
              {
                if(value & 1 << i)
                {
                  count++;
                }
              }
              if(count % 2)
              {
                value |= 1 << 7;
              }
              good = writeBuffer.add(value);
            }
            else
            {
              mode = error;
              Serial.println();
              Serial.println("Input error - abort");
              Serial.println();              
            }
            break;
          case binary:
            good = writeBuffer.add(value);
            break;
          case baudot:
            if(baudotBuffer.set(value))
            {
              while(baudotBuffer.charReady() && good)
              {
                good = writeBuffer.add(baudotBuffer.character());
              }
            }
            else
            {
              mode = error;
              baudotBuffer.reset();
              Serial.println();
              Serial.println("Input error - abort");
              Serial.println();              

            }
            break;
          default:
            mode = error;
            Serial.println("unexpected case!");
            writeBuffer.clear();
            break;
        }
        if(!good)
        {
          Serial.println("Buffer overflow");
          mode = error;
          hexBuffer.reset();
          humanBuffer.reset();
          decBuffer.reset();
          baudotBuffer.reset();
        }
      }
      else
      {
        Serial.println("Read error");
      }
    }

    // Flow control
    if(xonSendt && writeBuffer.almostFull())
    {
      Serial.write(XOFF);
      xonSendt = false;
    }
    else if(!xonSendt && !writeBuffer.almostFull())
    {
      Serial.write(XON);
      xonSendt = true;
    }

    // handle punching and simulation
    now = millis();
    if(isHigh && now > (lastTime + highTime))
    {
      if(!simulationMode)
      {
        digitalWrite(PinTransportHole, LOW);
        digitalWrite(PinTransportMotor, LOW);
        for(int i = 0; i < 8; i++)
        {
          digitalWrite(pins[i], LOW);
        }
      }
      isHigh = false;
      lastTime = now;
    }
    else if(!isHigh && now > (lastTime + lowTime) && writeBuffer.available())
    {
      if(simulationMode)
      {
        simulate(writeBuffer.take());
      }
      else
      {
        punch(writeBuffer.take());
      }
      isHigh = true;
      lastTime = now;
    }
    else if(mode == binary && now > (lastTime + waitTime))
    {
      mode = error;
      Serial.println("Timeout");
    }
  }
}

void simulate(byte character)
{
  for(int i = 0; i < 8; i++)
  {
    if(character & 1 << i)
    {
      Serial.print("o");
    }
    else
    {
      Serial.print(".");
    }
    if(i == 2)
    {
      Serial.print(":");
    }
  }
  Serial.println();
}

void punch(byte character)
{
  for(int i = 0; i < 8; i++)
  {
    if(character & 1 << i)
    {
      digitalWrite(pins[i], HIGH);
    }
  }
  digitalWrite(PinTransportHole, HIGH);
  digitalWrite(PinTransportMotor, HIGH);          
}

