#pragma once
#include "Arduino.h"
#include "Definitions.h"

class LightSensor {
  protected:
    byte pin;
  public:
    bool lightState = false;
    LightSensor(byte pin)
    {
      this->pin = pin;
      init();
    }
    void init()
    {
      pinMode(pin, INPUT);
    }
    void measureLight()
    {
      int value = analogRead(pin);
      if (value > LIGHT_THRESHOLD)
        lightState = true;
      else
        lightState = false;
    }
};