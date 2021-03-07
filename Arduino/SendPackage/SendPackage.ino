/*
 Name:		SendPackage.ino
 Created:	3/7/2021 7:31:19 PM
 Author:	Benjamin
*/

#include <string>

std::string myString;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	while (!Serial.available());
	while (Serial.available())
	{
		myString.push_back(Serial.read());
	}
	if (myString.compare("Hello.") == 0)
		Serial.println("Hello yourself.");
	else if (myString.compare("Bye.") == 0)
		Serial.println("Yeah bye.");
	else if (myString.compare("What?") >= 0)
		Serial.println("What size is my cock?");
	else
		Serial.println("I don't care motherfucker.");
}
