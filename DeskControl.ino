/*
This file is part of DeskControl.

DeskControl is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DeskControl is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with DeskControl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <DeskComms.h>
#include <LiquidCrystal.h>
DeskComms deskComms(7,6);
LiquidCrystal statusLCD(12, 10, 11, 2, 3, 4, 5);

#define VERSION "1.0"

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	deskComms.begin();
	statusLCD.begin(16, 2);
	pinMode(13, OUTPUT);
	statusLCD.write("WiDesk v");
	statusLCD.write(VERSION);
	statusLCD.setCursor(0,1);
	statusLCD.write("PC Not Connected");
}

void clearSecondLine(){
	statusLCD.clear();
	statusLCD.write("WiDesk v");
	statusLCD.write(VERSION);
}

void loop() {
	// put your main code here, to run repeatedly:
	if (Serial.available() > 0) {
		byte bytes[3];
		Serial.readBytes(bytes, 3);
		if (bytes[0] == 0x99 && bytes[1] == 0x61) {
			clearSecondLine();
			statusLCD.setCursor(0,1);
			statusLCD.write("PC Connected");
		} else if (bytes[0] == 0x90 || bytes[0] == 0x80) {
			//0x90 0x00 0x09
			// command, bank, channel
			// on, yellow bank, channel 9
			if (bytes[0]==0x90) {
				deskComms.toggleLightChannel((MasterColour)bytes[1], bytes[2], true);
			} else {
				deskComms.toggleLightChannel((MasterColour)bytes[1], bytes[2], false);
			}
		}
	}
}
