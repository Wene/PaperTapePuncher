/* This software is written for Arduino boards and turn it into a
   Control unit replacement for FACIT Paper tape puncher. */

#include "fifo.h"

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

int pins[] = {PinBit0, PinBit1, PinBit2, PinBit3, PinBit4, PinBit5, PinBit6, PinBit7};

enum writeMode {error, ascii, binary, hex, dec, baudot};
bool simulationMode = false;
enum baudotMode {letters, figures};
writeMode mode = error;

Fifo writeBuffer;

unsigned long lastTime = 0;
unsigned long now = 0;
unsigned long highTime = 2;
unsigned long lowTime = 18;
bool isHigh = false;
int value = 0;
byte letter = 0;

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
    Serial.println();
    Serial.println();
    Serial.println();
  }

  //print prompt
  Serial.println("Select mode: (A)SCII, (B)inary, (H)EX, (D)ecimal, (5)-Bit Baudot");
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
  while(Serial.available())
  {
    value = Serial.read();
    letter = value;
    Serial.println();
    
    switch(letter)
    {
      case 'h':
      case 'H':
        mode = hex;
        Serial.println("Enter HEX mode. Enter non HEX character to exit");
        break;
      case 'd':
      case 'D':
        mode = dec;
        Serial.println("Enter decimal mode. Enter 3-digit numbers. Invalid input to quit");
        break;
      case 'b':
      case 'B':    
        mode = binary;
        Serial.println("Enter binary mode. Reset to exit.");
        break;
      case 'a':
      case 'A':
        mode = ascii;
        Serial.println("Enter ASCII mode. Enter a char over 127 to exit.");
        break;
      case '5':
        mode = baudot;
        Serial.println("Enter 5-Bit Baudot mode. Press escape to exit.");
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
  }

  //punch in selected mode
  while(mode != error && 1)
  {
    while(Serial.available())
    {
      value = Serial.read();
      if(value >= 0 && value < 256)
      {
        switch(mode)
        {
          case hex:
            
            break;
          case dec:
            
            break;
          case ascii:

            break;
          case binary:

            break;
          case baudot:

            break;
          default:
            mode = error;
            Serial.println("unexpected case!");
            writeBuffer.clear();
            break;
        }
        if(!writeBuffer.add(letter))
        {
          Serial.println("Buffer overflow");
        }
      }
      else
      {
        Serial.println("Read error");
      }
    }
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

