  #include "DigiJoystick.h"

/*
Description:	Interfacing a NES controller with a PC with an Arduino.
 Coded by:	Prodigity
 Date:		1 December 2011
 Revision:	V0.93 (beta)
 Modified by:    Matt Booth (20 December 2014)
 Modificado por: Ernesto Bazzano (3 Diciembre 2015) bajo AGPL
 */

#define R B10000000
#define L B01000000
#define D B00100000
#define U B00010000
#define S B00001000
#define G B00000100
#define B B00000010
#define A B00000001

const int latch = 1; //am
const int clock = 2; // marron
const int data  = 5; // azul    

#define latchlow digitalWrite(latch, LOW)
#define latchhigh digitalWrite(latch, HIGH)
#define clocklow digitalWrite(clock, LOW)
#define clockhigh digitalWrite(clock, HIGH)
#define dataread digitalRead(data)

// http://www.mit.edu/~tarvizo/nes-controller.html
#define wait delayMicroseconds(12) //12

byte state = 0;

void setup() {

  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, INPUT);

  delay(20);
}

void loop() { 
  state = 0; 
  ReadNESjoy();
  DigiJoystick.delay(10);
} 


void ReadNESjoy() { 
  latchlow; 
  clocklow; 
  latchhigh; 
  wait; 
  latchlow; 
  state += !dataread * (1 << 0);    
  for (int i = 1; i < 8; i++) { 
    clockhigh; 
    wait; 
    state += !dataread * (1 << i); 
    clocklow; 
    wait;
  } 
 
  int buttonByte = 0;

  // flechas  
  DigiJoystick.setY((byte)(state & U?0:state & D?255:127));
  DigiJoystick.setX((byte)(state & L?0:state & R?255:127));

  // botones
  bitWrite(buttonByte, 0, (byte) (state & A));
  bitWrite(buttonByte, 1, (byte) (state & B));
  bitWrite(buttonByte, 2, (byte) (state & G));
  bitWrite(buttonByte, 3, (byte) (state & S));
  // envia los bites
  DigiJoystick.setButtons((byte) buttonByte, (byte) 0);


} 

