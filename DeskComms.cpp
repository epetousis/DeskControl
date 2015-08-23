#include "DeskComms.h"

DeskComms::DeskComms(int txPin, int rxPin) : _midiPort (txPin, rxPin) {
	_txPin = txPin;
	_rxPin = rxPin;
}

void DeskComms::begin() {
	_midiPort.begin(31250);
}

// Remember - pressing the flash button below a fader turns the light on
// even if the masters are turned down.
void DeskComms::toggleLightChannel(MasterColour master, int channel, bool state) {
	switch (master) {
		case YELLOW:
			if (state) // 0x91 is yellow bank, 0x92 is red bank
				_midiPort.write(0x91); // 0x9* is note on
			else
				_midiPort.write(0x81); // 0x8* is note off
			break;
		case RED:
			if (state) // 0x91 is yellow bank, 0x92 is red bank
				_midiPort.write(0x92); // 0x9* is note on
			else
				_midiPort.write(0x82); // 0x8* is note off
			break;
		default:
			return;
	}
	if (channel <= 0 || channel > 36)
		return;
	_midiPort.write(channel+48); // 31-54 is channels 1-36 +48
	_midiPort.write(0x7f); // TODO: check if using values other than 0x7f control brightness
	// cmd can't be greater than 127
	// data values can't be less than 127
}
