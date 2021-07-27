#pragma once
#include "Arduino.h"
#include "EEPROM.h"
#include "Definitions.h"

class MemoryManager {
  public:
    int sprayLeft = 0;
    unsigned long sprayDelay = 0;
    byte toSpray1 = 0;
    byte toSpray2 = 0;
    MemoryManager()
    {
      init();
    }
    void init()
    {
      // Check if EEPROM is empty, if so write default values. Otherwise get the values. 
      if (emptyCheck()) {
        resetSpray();
        setDelay(DEFAULT_TRIGGER_DELAY);
        setToSpray(1, DEFUALT_SPRAY_1);
        setToSpray(2, DEFAULT_SPRAY_2);
      } else {
        EEPROM.get(SPRAY_ADDR, sprayLeft);
        EEPROM.get(TRIGGER_DELAY_ADDR, sprayDelay);
        EEPROM.get(SPRAY_1_ADDR, toSpray1);
        EEPROM.get(SPRAY_2_ADDR, toSpray2);
      }
    }
    // check to see if values at EEPROM addresses are empty
    bool emptyCheck() {
      byte value = 0;
      for (unsigned int addr = SPRAY_ADDR; addr < EEPROM.length(); addr++) {
        value = EEPROM.read(addr);
        // assumed is that an erased EEPROM normally reads as 0xFF. 
        if (value != 255) {
          return false;
        }
      }
      return true; 
    }
    void readMemory(bool removeValues)
    {
      byte value = 0;
      int length = 8; // EEPROM.length(); 
      for (int address = 0; address < length; address++)
      {
        // read old values
        value = EEPROM.read(address);
        Serial.print(address);
        Serial.print(F("\t"));
        Serial.print(value, DEC);
        Serial.println();
        if (removeValues) {
          // empty value at address
          EEPROM.write(address, 255);
          // read new values
          value = EEPROM.read(address);
          Serial.print(address);
          Serial.print(F("\t"));
          Serial.print(value, DEC);
          Serial.println();
        }
      }
    }
    void setDelay(unsigned long sprayDelay)
    {
      this->sprayDelay = sprayDelay;
      EEPROM.put(TRIGGER_DELAY_ADDR, sprayDelay);
    }
    void setToSpray (byte n, byte val) {
      int addr; 
      switch (n) {
        case 1:
          this->toSpray1 = val;
          addr = SPRAY_1_ADDR;
          break;
        case 2: 
          this->toSpray2 = val;
          addr = SPRAY_2_ADDR;
          break;
        default:
          break;
      }
      EEPROM.put(addr, val);
    }
    byte getToSpray(byte n) {
      switch (n) {
        case 1:
          return toSpray1;
        case 2:
          return toSpray2;
        default:
          return 0;
      }
    }
    void setSprayLeft(int sprayLeft) {
      this->sprayLeft = sprayLeft; 
      EEPROM.put(SPRAY_ADDR, sprayLeft);
    }
    void decreaseSpray() {
      setSprayLeft(sprayLeft - 1);
    }
    void resetSpray()
    {
      setSprayLeft(DEFAULT_SPRAY_VAL);
    }
};
