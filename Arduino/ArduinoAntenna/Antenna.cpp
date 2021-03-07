#include "Antenna.h"

/*	The cc1101 internally represents a frequency in three byte registers resembling a low, middle and high part of a 24 bit number
*	The carrier frequency is then calculated by the following formula:
*	For the crystal oscillator frequency c and the frequency register value (summed up) fr:
*	f = c * fr / 2^16
*/
void antennas::Antenna::setFrequency(int f)
{
	byte f0, f1, f2;

	long fScaled = f * 65536;	// f*2^16
	fScaled /= xosc;	// divided by c

}
