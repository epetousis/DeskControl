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
DeskComms deskComms(1,0);
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

void loop() {
	// put your main code here, to run repeatedly:
	deskComms.toggleLightChannel(YELLOW, 2, true);
	delay(500);
}
