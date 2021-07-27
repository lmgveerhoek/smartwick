#pragma once
#include "Arduino.h"

class MotionSensor {
  protected:
    byte pin;
  public:
    bool motionState = false;
    bool isToggled = false;
    MotionSensor(byte pin)
    {
      this->pin = pin;
      init();
    }
    void init()
    {
      pinMode(pin, INPUT);
    }
    void measureMotion()
    {
      if (digitalRead(pin) == HIGH)
      {
        isToggled = !motionState;
        motionState = true;
      }
      else
      {
        isToggled = false;
        motionState = false;
      }
    }
};