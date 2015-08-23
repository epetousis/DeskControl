#include <SoftwareSerial.h>

#ifndef DeskComms_h
#define DeskComms_h

enum MasterColour { YELLOW, RED };

class DeskComms
{
	public:
		DeskComms(int txPin, int rxPin);
		void begin();
		void toggleLightChannel(MasterColour master, int channel, bool state);
	private:
		SoftwareSerial _midiPort;
		int _txPin;
		int _rxPin;
};

#endif
