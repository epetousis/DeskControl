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

//comment out for full brightness LED.
#define DIMLIGHT 1

#ifdef DIMLIGHT
#define MAX_ANALOG_VAL 255
#define MIN_ANALOG_VAL 240
#define FADE_INTERVAL 50
#else
#define MIN_ANALOG_VAL 0
#define MAX_ANALOG_VAL 255
#define FADE_INTERVAL 5
#endif

void rgbFadeToColour(int fromColour, int toColour) {
	// if pin == -1
	int toPin = 9 + toColour;
	int fromPin = 9 + fromColour;
	if (fromColour >= 0 && toColour >= 0) {
		int i, j;
		for (i = MIN_ANALOG_VAL, j = MAX_ANALOG_VAL; j >= MIN_ANALOG_VAL; i++, j--) {
			analogWrite(fromPin, i);
			analogWrite(toPin, j);
			delay(FADE_INTERVAL);
		}
		return;
	} else if (fromColour < 0) {
		for (int i = MAX_ANALOG_VAL; i >= MIN_ANALOG_VAL; i--) {
			analogWrite(toPin, i);
			delay(FADE_INTERVAL);
		}
	} else if (toColour < 0) {
		for (int i = MIN_ANALOG_VAL; i <= MAX_ANALOG_VAL; i++) {
			analogWrite(fromPin, i);
			delay(FADE_INTERVAL);
		}
	}
}

void pulseColour(int colour) {
	rgbFadeToColour(-1, colour);
	delay(500);
	rgbFadeToColour(colour, -1);
}

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	deskComms.begin();
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	digitalWrite(9, HIGH); // red
	digitalWrite(10, HIGH); // green
	digitalWrite(11, HIGH); // blue
}

bool connected = false;
long times = 0;

void loop() {
	// put your main code here, to run repeatedly:
	if (!connected) {
		pulseColour(2);
	} else if (times > 0) {
		times++;
		if (times >= 1000000) {
			times = 0;
			rgbFadeToColour(1, -1);
		}
	}
	if (Serial.available() > 0) {
		byte bytes[3];
		Serial.readBytes(bytes, 3);
		if (bytes[0] == 0x99 && bytes[1] == 0x61) {
			connected = true;
			rgbFadeToColour(-1, 1);
			times = 1;
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
