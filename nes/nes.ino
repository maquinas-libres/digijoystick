#include "DigiJoystick.h"
//#include "DigiKeyboard.h"
/*
Description:	Interfacing a NES y SNES controller with a PC with an Arduino.
 Coded by:	Prodigity
 Date:		1 December 2011
 Revision:	V0.93 (beta)
 Modified by:    Matt Booth (20 December 2014)
 Modificado por: Ernesto Bazzano (3 Diciembre 2015-21 Noviembre 2016) bajo AGPL
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
byte state1 = 0;

void setup() {

  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, INPUT);

  delay(20);
}

void loop() { 
  state = 0; 
  state1 = 0; 
  ReadNESjoy();
  DigiJoystick.delay(10);
} 


void ReadNESjoy() { 
 // DigiKeyboard.print("\n");
  latchlow; 
  clocklow; 
  latchhigh; 
  wait; 
  latchlow; 
  state += !dataread * (1 << 0);
  for (int i = 1; i < 16; i++) { 
    clockhigh; 
    wait; 
    if (i < 8) state += !dataread * (1 << i); else  {
      state1 += !dataread * (1 << (i-7)); 
    //  DigiKeyboard.print(!dataread == true?"1":"0");
    }
    clocklow; 
    wait;
  } 
  int buttonByte = 0;

  // flechas  
  DigiJoystick.setY((byte)(state & U?0:state & D?255:127));
   DigiJoystick.setX((byte)(state & L?0:state & R?255:127));
//  if (!state || !state1) DigiKeyboard.sendKeyStroke(0);
    
  // botones
  bitWrite(buttonByte, 0, (byte) (state & A));
  bitWrite(buttonByte, 1, (byte) (state & B));
  bitWrite(buttonByte, 2, (byte) (state & G));
  bitWrite(buttonByte, 3, (byte) (state & S));
  
  bitWrite(buttonByte, 4, (byte) (state1 & B));
  bitWrite(buttonByte, 5, (byte) (state1 & G));
  bitWrite(buttonByte, 6, (byte) (state1 & S));
  bitWrite(buttonByte, 7, (byte) (state1 & U));
  
  // envia los bites
DigiJoystick.setButtons((byte) buttonByte, (byte) 0); 



}


