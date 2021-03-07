/*
 Name:		SendPackages.ino
 Created:	3/5/2021 2:11:41 PM
 Author:	Benjamin
*/

// the setup function runs once when you press reset or power the board
#include <ELECHOUSE_CC1101.h>
#include <RegisterSettings.h>

// abbreviation
ELECHOUSE_CC1101* ptr;

namespace proper
{
	template <typename T, size_t N>
	constexpr size_t length(T(&)[N]) { return N; }
}

void setup() {
	ptr = &ELECHOUSE_cc1101;	// abbreviation

	// configure the cc1101 by adjusting the register values according to the file exported from smartrf studio:
	for (int i = 0; i < proper::length(preferredSettings); i++)	// iterates through all changed register values
	{
		ptr->SpiWriteReg(preferredSettings[i].reg, preferredSettings[i].value);	// writes to the register via the spi interface
	}


}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
