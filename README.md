# Arduino-Dice-Board
Arduino Dice Switchboard


Description
------------
Dice board software for use with the TM1637 7-Segment Display and the Arduino Uno. Rolls the selected dice based on the switch and displays it on screen. This uses external libraries to handle the display module.

Installation
------------
If using the arduino IDE:
	Copy TM1637-master to your arduino libraries, make sure that it appears as a contributed library

On the circuit board: 
	Set up the display CLK & DIO to pins 8 & 9, respectively.
	Wire inputs to digital pins 2 through 7.

Schematic 
------------
Coming Soon

Usage 
-------------
Pressing a switch will display the selected dice on screen. Releasing the switch will then display a random number based on the selection.


Thanks to avishorp for the great [library](https://github.com/avishorp/TM1637) they provided for the TM1637.
