#pragma once
#include "Arduino.h"
#include "DallasTemperature.h"
#include "Definitions.h"

class Tempsensor {
  protected:
    byte pin;
    unsigned long lastMillis;
    OneWire oneWire;
    DallasTemperature sensors;
    DeviceAddress deviceAddress;
  public:
    Tempsensor(byte pin) : lastMillis(0) {
      this->pin = pin;
      oneWire = OneWire(pin);
      sensors = DallasTemperature(&oneWire);
      init();
    }
    void init() {
      // set resolution to 9 bit and use non-blocking temperature requests
      sensors.begin();
      sensors.getAddress(deviceAddress, 0);
      sensors.setResolution(deviceAddress, 9);
      sensors.setWaitForConversion(false);
      sensors.requestTemperatures();
    }

    void requestNewTemperature() 
    {
      sensors.requestTemperatures(); 
    }

    float getTemperature() 
    {
      return sensors.getTempC(deviceAddress); 
    }
}; 





  