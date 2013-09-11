/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "milliMATRIX.h"

Millimatrix::Millimatrix()
{
  int pins[17] = {-1, 7, 17, 15, 16, 14, 11, 3, 2, 4, 12, 6, 8, 9, 10, 5, 13};
  for (int i = 1; i <= 16; i++)
  {
	pinMode(pins[i], OUTPUT);
  }  
}
