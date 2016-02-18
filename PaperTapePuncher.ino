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

Fifo writeBuffer;

unsigned long lastTime = 0;
unsigned long now = 0;
unsigned long highTime = 2;
unsigned long lowTime = 18;
bool isHigh = false;
int value = 0;
bool ok = false;

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
  
  delay(5000);
  Serial.println("Ready");
}

void loop() {
  while(Serial.available())
  {
    value = Serial.read();
    if(value >= 0 && value < 256)
    {
      if(!writeBuffer.add(value))
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
    digitalWrite(PinTransportHole, LOW);
    digitalWrite(PinTransportMotor, LOW);
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(pins[i], LOW);
    }
    isHigh = false;
    lastTime = now;
  }
  else if(!isHigh && now > (lastTime + lowTime))
  {
    value = writeBuffer.take(ok);
    if(ok)
    {      
      // Insert punching here...
      Serial.print("Punching ");
      Serial.println(char(value));
            
      isHigh = true;
      lastTime = now;
    }
  }
}

/*

  for(int i = 0; i < 8; i++)
  {
    digitalWrite(pins[i], HIGH);
    digitalWrite(PinTransportHole, HIGH);
    digitalWrite(PinTransportMotor, HIGH);
    delay(2);
    digitalWrite(pins[i], LOW);
    digitalWrite(PinTransportHole, LOW);
    digitalWrite(PinTransportMotor, LOW);
    delay(18);
  }

*/

