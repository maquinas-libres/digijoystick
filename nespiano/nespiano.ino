#include "DigiKeyboard.h"

// Nota: necesita la version modifcada de "DigiKeyboard.h"

/*
Description:	Interfacing a NES controller with a PC with an Arduino.
 Coded by:	Prodigity
 Date:		1 December 2011
 Revision:	V0.93 (beta)
 Modified by:    Matt Booth (20 December 2014)
 Modificado por: Ernesto Bazzano (7 al 9 Febrero 2016) bajo AGPL
 */

#define R B10000000
#define L B01000000
#define D B00100000
#define U B00010000
#define S B00001000
#define G B00000100
#define B B00000010
#define A B00000001

#define KEY_ARROW_LEFT  0x50
#define KEY_ARROW_RIGHT 0x4F

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

int octava = 4;
int oct_sentido = 0;

void setup() {
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, INPUT);
}

void loop() { 
  state = 0; 
  ReadNESjoy();
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
   /*
  hay que cambiar las flechas por teclas
  qwertyu
  LURDSAB
  G flechas: izquierda y derecha
  */

    // para tocar la clave con vmpk
 
    if (!state) DigiKeyboard.sendKeyStroke(0);
    
    // manejo de octavas
    if (state &  G)  {
      if (oct_sentido == 0)  {
         DigiKeyboard.sendKeyStroke(KEY_ARROW_RIGHT);
        octava ++;
        if (octava > 7) oct_sentido = 1;
      } else {
         DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
        octava --;
        if (octava < 1) oct_sentido = 0;
      }
      N = 0;
      return;
    }
    // notas

    if (state & L) DigiKeyboard.print("q");
    if (state & U) DigiKeyboard.print("w");
    if (state & R) DigiKeyboard.print("e");
    if (state & D) DigiKeyboard.print("r");
    if (state & S) DigiKeyboard.print("t");
    if (state & A) DigiKeyboard.print("u");
    if (state & B) DigiKeyboard.print("y");
} 


/*
  Quehaceres
  ==========
  
  - select necesita un delay
  
*/
