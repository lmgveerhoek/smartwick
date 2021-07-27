# airwickass

Features:
- Stores delay and sprays left to EEPROM and loads them during startup
- Uses F macro to read strings from PROGMEM
- Uses pin 13 for the mosfet, so during development the AirWick doesn't have to be connected 
- Has a cable routing, such that there is no interference during updating of the program
- Updates the temperature every two seconds, always displaying except while in the menu
- A menu that allows to change the amount of sprays per usage, set the delay, see the current sprays left and able to reset them. 
