/* This software is written for Arduino boards and turn it into a
   Control unit replacement for FACIT Paper tape puncher. */

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

#define BufferSize 10

int pins[] = {PinBit0, PinBit1, PinBit2, PinBit3, PinBit4, PinBit5, PinBit6, PinBit7};

byte buffArray[BufferSize]; // Buffer array, used as ring buffer
int buffWritePos = 0;       // Write position - write at this position, increment afterwards.
int buffReadPos = 0;        // Read position - read at this position, increment afterwards.
int buffLevel = 0;          // Distance between read and write position. Overflow detected when larger than BufferSize 
int buffValue;

int lastTime = 0;
int highTime = 20;
int lowTime = 180;
bool isHigh = false;

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
  while(Serial.available())
  {
    buffValue = Serial.read();
    if(buffValue >= 0 && buffValue <= 255)
    {
      buffArray[buffWritePos] = buffValue;
      buffWritePos++;
      buffLevel++;
      if(buffWritePos >= BufferSize)
      {
        buffWritePos = 0;
      }
      if(buffLevel > BufferSize) {
        Serial.println("Buffer overflow");
      }
    }
  }
  
  if(isHigh)
  {
    if(millis() > lastTime + highTime)
    {
      digitalWrite(PinTransportHole, LOW);
      digitalWrite(PinTransportMotor, LOW);
      for(int i = 0; i < 8; i++)
      {
        digitalWrite(pins[i], LOW);
      }
      isHigh = false;
      lastTime = millis();
    }
  }
  else
  {
    if(millis() > lastTime + lowTime)
    {
      if(buffLevel)
      {
        buffValue = buffArray[buffReadPos];
        buffReadPos++;
        buffLevel--;
        if(buffReadPos >= BufferSize)
        {
          buffReadPos = 0;
        }
        
        // Insert punching here...
        Serial.print("Punching ");
        Serial.println(char(buffValue));
        
        isHigh = true;
        lastTime = millis();
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

}
