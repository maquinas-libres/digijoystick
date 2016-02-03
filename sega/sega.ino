#include "DigiJoystick.h"

/*
Description:	Interfacing a SEGA controller with a PC with an Arduino.
 Coded by:	Prodigity
 Date:		1 December 2011
 Revision:	V0.93 (beta)
 Modified by:    Matt Booth (20 December 2014)
 Modificado por: Ernesto Bazzano (3 y 23 Diciembre 2015) bajo AGPL
 */

#define R B10000000
#define L B01000000
#define D B00100000
#define U B00010000
#define S B00001000
#define G B00000100
#define B B00000010
#define A B00000001

const int BA = 0;
const int BB = 1;
const int BC = 2;
const int BX = 3;
const int BY = 4;
const int BZ = 5;
const int BS = 6;
const int BM = 7;

const int latch = 1; //am
const int clock = 2; // marron
const int data  = 5; // azul    

const int slc = 0; // flag

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
  
  pinMode(slc, OUTPUT);
  digitalWrite(slc, HIGH);
  
  delay(20);
}

void loop() { 
  ReadNESjoy();
  DigiJoystick.delay(10);
} 


void ReadNESjoy() { 
  
  int buttonByte = 0;
  
  for (int x = 0; x < 8; x++) { 
    state = 0;
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
 
  // teclas de sega   
  if (x == 0 ) {
    // flechas
      DigiJoystick.setY((byte)(state & U?0:state & D?255:127));
      DigiJoystick.setX((byte)(state & L?0:state & R?255:127));
      // otra cruz
    /*
      DigiJoystick.setZROT((byte)(state & U?0:state & D?255:127));
      DigiJoystick.setSLIDER((byte)(state & L?0:state & R?255:127));
     */
  } else if (x < 4 ) {
      if ( x%2 == 0 ) {
        // B y C
          bitWrite(buttonByte, BB, (byte)(state & A));
          bitWrite(buttonByte, BC, (byte)(state & B));
      } else { 
        // A y Select
          bitWrite(buttonByte, BA, (byte)(state & A));
          bitWrite(buttonByte, BS, (byte)(state & B));
      }
  } 
  // la otra dimension
  if (x == 6)  {
      bitWrite(buttonByte, BX, (byte) ((byte)(state & L)));
      bitWrite(buttonByte, BY, (byte) ((byte)(state & D)));
      bitWrite(buttonByte, BZ, (byte) ((byte)(state & U)));
      bitWrite(buttonByte, BM, (byte) ((byte)(state & R)));
   }


/*
botones de sega 
==============

Cycle	TH out	TR in	TL in	D3 in	D2 in	D1 in	D0 in
0	HI	C	B	Right	Left	Down	Up
1	LO	Start	A	0	0	Down	Up
2	HI	C	B	Right	Left	Down	Up
3	LO	Start	A	0	0	Down	Up
4	HI	C	B	Right	Left	Down	Up
5	LO	Start	A	0	0	0	0
6	HI	C	B	Mode	X	Y	Z
7	LO	Start	A	---	---	---	---
*/


  // envia los bites
  DigiJoystick.setButtons((byte) buttonByte, (byte) 0); 
  digitalWrite(slc, !digitalRead(slc));

}

} 

