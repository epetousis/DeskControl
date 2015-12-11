# DeskControl
Control an LSC Maxim lighting desk over MIDI using Arduino.

### Limitations
* LSC's MIDI controller does not have the ability to control channel brightness; you can only toggle a light on and off.

### Notes
* Using MIDI to do this sucks. Use DMX instead, it isn't brand dependent and is easier to code for (use a library).
