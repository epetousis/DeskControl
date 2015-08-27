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

#include <SoftwareSerial.h>

#ifndef DeskComms_h
#define DeskComms_h

enum MasterColour { YELLOW, RED };

class DeskComms
{
	public:
		DeskComms(int rxPin, int txPin);
		void begin();
		bool readLightChannel(MasterColour master, int channel);
		void toggleLightChannel(MasterColour master, int channel, bool state);
	private:
		SoftwareSerial _midiPort;
		int _txPin;
		int _rxPin;
};

#endif
