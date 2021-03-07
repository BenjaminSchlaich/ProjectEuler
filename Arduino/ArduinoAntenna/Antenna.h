#pragma once

// Keep everything clean and without confusion with this namespace that contains everything related to the antenna interface
namespace antennas
{
	// These are the modulation schemes available with the cc1101
	typedef enum ModulationScheme { ASK, FSK_2, FSK_4, OOK, GFSK, MSK};

	/*
		This class gives an easy to use Interface for the cc1101 transceiver.
		It handles all communication with the transceiver via the SPI interface automatically, so you don't have to worry about that.
		When constructing an instance of Antenna the SPI communication will be set up first.
		If no parameters are passed the settings have to be adjusted using the practical member functions.
		The default parameters will make the antenna be in PACKAGE mode sending at 433Hz using ASK.
		
	*/
	class Antenna
	{
	public:

		// Set the carrier frequency to f, an integer in kHz
		void setFrequency(int f);

		// Set the signal modulation scheme (amplitude shift keying, frequency shift keying, etc.)
		void setModulation(ModulationScheme ms);



	private:

		// The crystal oscillator frequency in Hz
		long xosc = 26000000;
	};

}	// namespace antennas