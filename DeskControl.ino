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
